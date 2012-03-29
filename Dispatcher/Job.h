#ifndef JOB_H
#define	JOB_H

#include <set>
#include <deque>
#include <map>
#include <string>
#include <common/common.h>
#include "RunCondition.h"

// stub, flesh this out a little better
// (we formally defined this as a job attribute)
// right now we are checking is a particular case is true (not zero)

typedef uint32_t jobID;

struct JobStruct {
    jobID id;
    std::string psName;
    std::deque<bbtag> conditions;
};

class Job {
public:
    Job();
    ~Job();

    pid_t pid;
    std::string psName;

    enum JobState {
        STOPPED, RUNNING, GRACE
    };

    JobState state;

    bool start();
    bool stop();
    bool enterGrace();

    void updateState(const std::map<bbtag, DataPoint>&);
    //private:

    std::deque<RunCondition> conditions;
    std::map<bbtag, RunCondition*> reverseMapping;

};

#endif	/* JOB_H */

