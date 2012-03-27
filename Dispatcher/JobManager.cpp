#include "JobManager.h"


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
    // for each job from the new list of jobs
    for (std::deque<JobStruct>::const_iterator it = jobstruct.begin(); it != jobstruct.end(); ++it) {
        // if a job does not exist, create it and return the Job object for it
        Job& job = jobSet[it->id].job;


        if (job.psName != it->psName) {
            // stop old and start new


            // tell the process to quit gracefully
            job.enterGrace();

            // TODO: garbage collect the process and wait until it dies or we have to kill it


        }
    }
}

void JobManager::update() {

}

void JobManager::eventLoop() {
    // loop forever
    while(true) {
        std::deque<ControlShell*> allCS;
        // decide what might need attention
        
        for (std::map<bbtag, CSDetails>::const_iterator it = CSSet.begin(); it != CSSet.end(); ++it) {
            allCS.push_back(&(it->second.controlShell));
        }
        
        // wait for one (or more) to call for attention
        ControlShell::multiWait(allCS);
        
        // act based on that
        for (std::deque<ControlShell*>::const_iterator it = allCS.begin(); it != allCS.end(); ++it) {
            it->processMsgQueue();
            it->checkForUpdates();
        }   
    }
}

void jobManagerUpdateCallback(bbtag _tag, const DataPoint& point) {
    JobManager::getInstance()->update(_tag, point);
}
