#ifndef JOBMANAGER_H
#define	JOBMANAGER_H

#include <set>
#include <map>
#include <deque>
#include "Job.h"
#include <common/DataPoint.h>
#include <common/ControlShell.h>

struct JobDetails {
    Job job;
};

struct CSDetails {

    inline CSDetails() : controlShell(0) {
    }

    ControlShell controlShell;
};

void jobManagerUpdateCallback(bbtag, const DataPoint&);

class JobManager {
public:
    void reload(std::deque<JobStruct>);

    void update(bbtag, const DataPoint&);

    void eventLoop();

    static JobManager* getInstance();

    void __debug__print();

private:
    std::map<jobID, JobDetails> jobSet;
    std::map<bbtag, CSDetails> csSet;
    std::map<bbtag, DataPoint> dataMap;

    // instancing
    static JobManager* instance;
    JobManager();

};

#endif	/* JOBMANAGER_H */

