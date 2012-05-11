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

#include <fstream>
#include <string>
#include <sstream>
#include "common/common.h"
#include "JobManager.h"
#include <common/KnowledgeSource.h>

#include <iostream>

const std::string jobfileName = "jobs.txt";

// TODO: merge this with JobManager (i think)

bool loadJobs() {
    std::ifstream jobfile(jobfileName.c_str());
    std::string line;

    std::deque<JobStruct> jobList;

    while (!jobfile.fail()) {
        JobStruct js;
        std::getline(jobfile, line);

        if (jobfile.fail()) {
            break;
        }

        std::cout << line << std::endl;


        std::istringstream linestream(line);
        linestream >> js.id >> js.psName;
        while (!linestream.fail()) {
            bbtag tag;
            linestream >> tag;
            if (linestream.fail()) {
                break;
            }

            js.conditions.push_back(tag);
        }

        jobList.push_back(js);
    }

    JobManager::getInstance()->reload(jobList);
    
    std::cout << "Loaded" << std::endl;

    return true;
}

int main(int argc, char** argv) {
    DataPoint p;
    KnowledgeSource a(0);
    a.connectKS();
    p.wrap(0);
    a.update(p);
    a.disconnectKS();
    KnowledgeSource b(1);
    b.connectKS();
    p.wrap(1);
    b.update(p);
    b.disconnectKS();

    // load joblist
    log("Loading initial jobs...\n");
    loadJobs();

    JobManager::getInstance()->__debug__print();

    log("Starting event loop...\n");
    // CS event loop
    JobManager::getInstance()->eventLoop();

    return 0;
}

