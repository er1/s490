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

