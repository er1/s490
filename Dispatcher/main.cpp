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

