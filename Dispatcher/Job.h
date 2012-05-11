/*
   Copyright 2012 Corey Clayton, Eric Chan, Mathieu Dumais-Savard

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

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

