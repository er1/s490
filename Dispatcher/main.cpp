#include <fstream>
#include <string>
#include <sstream>
#include "common/common.h"
#include "JobManager.h"

const std::string jobfileName = "jobs.txt";

bool loadJobs() {
    std::ifstream jobfile(jobfileName.c_str());
    std::string line;

    std::deque<JobStruct> jobList;

    while (!jobfile.fail()) {
        JobStruct js;
        std::getline(jobfile, line);
        std::istringstream linestream(line);
        linestream >> js.id >> js.psName;
        while (!linestream.fail()) {
            bbtag tag;
            linestream >> tag;
            js.conditions.push_back(tag);
        }

    }

    JobManager::getInstance()->reload(jobList);

    return true;
}

int main(int argc, char** argv) {

    // load joblist
    loadJobs();

    // CS event loop
    JobManager::getInstance()->eventLoop();

    return 0;
}

