#ifndef JOB_H
#define	JOB_H

#include <set>
#include <common/common.h>

// stub, flesh this out a little better
// (we formally defined this as a job attribute)
// right now we are checking is a particular case is true (not zero)

class RunCondition {
public:
    bbtag tag;
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

    std::set<RunCondition> conditions;

    bool start();
    bool stop();
    bool enterGrace();
private:

};

#endif	/* JOB_H */

