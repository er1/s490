#ifndef JOBMANAGER_H
#define	JOBMANAGER_H

#include <map>
#include <deque>
#include "Job.h"
#include <common/DataPoint.h>
#include <common/ControlShell.h>

struct jobDetails {
    Job job;
    std::set<bbtag> depends;
};

struct CSDetails {
    ControlShell controlShell;
    std::set<jobID> depends;
};

void jobManagerUpdateCallback(bbtag, const DataPoint&);

class JobManager {
public:
    void reload(std::deque<JobStruct>);

    void update(bbtag);

    void eventLoop();
    
    static JobManager* getInstance();

private:
    std::map<jobID, jobDetails> jobSet;
    std::map<bbtag, CSDetails> CSSet;

    // instancing
    static JobManager* instance;
    JobManager();

};

#endif	/* JOBMANAGER_H */

