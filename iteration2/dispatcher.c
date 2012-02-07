#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "common.h"
#include "jobdef.h"

// create the process for a job
int job_spawn(job_instance* job) {
	pid_t pid;

	// return if null pointer
	if (job == NULL) {
		return JOB_ERROR;
	}
	
	// return if process exists
	if (job->running) {
		return JOB_SUCCESS;
	}

	// create a new process if not
	pid = vfork();

	// handle the child spawning
	if (pid == 0) {
		// run the new process executable
		job->ps_name && execve(job->ps_name);

		// exit if a failiure occurs
		_exit(-1);
	}

	// error if new process cannot be created
	if (pid == -1) {
		job->running = 0;
		job->pid = 0;
		return JOB_ERROR;
	}

	// set various internal state conditions
	job->running = 1;
	job->pid = pid;

	return 0;
}

// allow a job to run
int job_allow(job_instance* job) {
	if (job == NULL) {
		return JOB_ERROR;
	}

	if (!job->running) {
		job_spawn(job);
	} else {
		// send SIGCONT
	}
	return JOB_SUCCESS;
}

int job_block(job_instance* job) {
	if (job == NULL) {
		return JOB_ERROR;
	}

	if (!job->running) {
		return 0;
	}

	// SEND SIGSTOP
}

	// spawn a new process
	// start a paused process

// stop a job from running
	// notify process to cease running
	// force pause a process
	// kill a process under extreme condition

// recv commands through some means

int main() {

	log("Starting up...\n");

	log("Shutting down...\n");

	return 0;
}
