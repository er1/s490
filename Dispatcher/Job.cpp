#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string>
#include "Job.h"

Job::Job() {
    pid = -1;
    psName.clear();
    state = STOPPED;
}

Job::~Job() {
    if (pid > 0)
        kill(pid, SIGKILL);
}

bool Job::start() {
    // if we have a process already running
    if (pid > 0) {
        // it is running, send SIGCONT (continue)
        if (kill(pid, SIGCONT) != 0) {
            // TODO: define behavior for continue not working
            return false;
        }
        return true;
    }

    // if we are here we do not have a process running;

    // create a new process
    pid = vfork();

    // handle the child spawning
    if (pid == 0) {
        // run the new process executable
        if (psName.size() > 0) {
            // WTF??
            // ??? newargv[] = {psName.c_str(), NULL};
            char* newenv[] = {NULL};
            execve(psName.c_str(), /*newargv*/ newenv, newenv);
        }

        // exit if a failure occurs
        _exit(-1);
    }

    // error if new process cannot be created
    if (pid == -1) {
        state = STOPPED;
        return false;
    }

    // set various internal state conditions
    state = RUNNING;

    return true;
}

bool Job::stop() {
    if (state == STOPPED) {
        return true;
    }

    // send SIGSTOP (stop)
    if (kill(pid, SIGSTOP) != 0);
    {
        // it didn't work if we are here, return false (meaning our request failed)
        return false;
    }

    state = STOPPED;
    return true;
}

bool Job::enterGrace() {
    if (state == STOPPED) {
        return true;
    }

    if (state == RUNNING) {
        state = GRACE;
        if (kill(pid, SIGUSR1) != 0) {
            // it didn't work if we are here, return false (meaning our request failed)
            return false;
        }
        return true;
    }

    if (state == GRACE) {
        return true;
    }

    return false; // never hit
}

void Job::updateState(const std::map<bbtag, DataPoint>& tagmap) {
    bool shouldRun = false;
    for (std::deque<RunCondition>::iterator it = conditions.begin(); it != conditions.end(); ++it) {
        if (it->canRun(tagmap)) {
            shouldRun = true;
            break;
        }
    }

    if (shouldRun) {
        start();
    } else {
        stop();
        // enterGrace();
    }
}