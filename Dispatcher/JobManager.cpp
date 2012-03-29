#include "JobManager.h"

#include <set>

// Singleton instance
JobManager* JobManager::instance = 0;

JobManager::JobManager() {
}

JobManager* JobManager::getInstance() {
    if (!instance)
        instance = new JobManager;
    return instance;
}

void JobManager::reload(std::deque<JobStruct> jobstruct) {
    std::set<bbtag> updates;

    // for each job from the new list of jobs
    for (std::deque<JobStruct>::const_iterator it = jobstruct.begin(); it != jobstruct.end(); ++it) {

        // get the new job descriptor
        const JobStruct& js = *it;

        // get the current job descriptor
        Job& job = jobSet[js.id].job;

        job.pid = 0;
        job.psName = js.psName;
        job.state = Job::STOPPED;

        for (std::deque<bbtag>::const_iterator rcit = js.conditions.begin(); rcit != js.conditions.end(); ++rcit) {
            bbtag tag = *rcit;
            
            // create and register for a CS if we need it (w/ callback)
            if (csSet.find(tag) == csSet.end()) {
                csSet[tag].controlShell = ControlShell(tag);
                csSet[tag].controlShell.connectCS();
                dataMap[tag] = csSet[tag].controlShell.getMostRecent();
                csSet[tag].controlShell.registerCallback(jobManagerUpdateCallback);
                if (updates.find(tag) == updates.end()) {
                    updates.insert(tag);
                }
            }
            
            job.conditions.push_back(RunCondition(*rcit));
        }
    }

    // lazy update 
    // TODO: do it properly
    for (std::set<bbtag>::const_iterator it = updates.begin(); it != updates.end(); ++it) {
        update(*it, dataMap[*it]);
    }
}

void JobManager::update(bbtag tag, const DataPoint& p) {
    dataMap[tag] = p;
    for (std::map<jobID, JobDetails>::iterator it = jobSet.begin(); it != jobSet.end(); ++it) {
        it->second.job.updateState(dataMap);
    }
}

void JobManager::eventLoop() {
    // loop forever
    while (true) {
        std::deque<BlackboardConnection*> allCS;
        // decide what might need attention

        for (std::map<bbtag, CSDetails>::iterator it = csSet.begin(); it != csSet.end(); ++it) {
            allCS.push_back(&(it->second.controlShell));
        }

        // wait for one (or more) to call for attention
        BlackboardConnection::multiWait(allCS);

        // act based on that
        for (std::deque<BlackboardConnection*>::iterator it = allCS.begin(); it != allCS.end(); ++it) {
            ((ControlShell*) * it)->processMsgQueue();
            ((ControlShell*) * it)->checkForUpdates();
        }
    }
}

void jobManagerUpdateCallback(bbtag _tag, const DataPoint& _point) {
    JobManager::getInstance()->update(_tag, _point);
}


// debug includes, remove later
#include <iostream>
using namespace std;

void JobManager::__debug__print() {
    cout << "====" << endl;
    for (std::map<bbtag, CSDetails>::const_iterator it = csSet.begin(); it != csSet.end(); ++it) {
        cout << "BBTAG\t" << it->first << endl;
    }
    cout << "----" << endl;
    for (std::map<jobID, JobDetails>::const_iterator it = jobSet.begin(); it != jobSet.end(); ++it) {

        cout << "JOBID\t" << it->first << "(" << it->second.job.psName << " " << it->second.job.state << ")" << ":";

        for (std::deque<RunCondition>::const_iterator it2 = it->second.job.conditions.begin(); it2 != it->second.job.conditions.end(); ++it2) {
            cout << " " << it2->tag;
        }
        cout << endl;
    }
    cout << "----" << endl;
}