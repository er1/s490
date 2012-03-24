#include <fstream>
#include <string>
#include <sstream>
#include "common/common.h"
#include "Job.h"

const std::string jobfileName = "jobs.txt";

bool loadJobs() {
    std::ifstream jobfile(jobfileName.c_str());
    std::string line;

    while (!jobfile.fail()) {
        std::getline(jobfile, line);
        std::ostringstream linestream(line);
        
        
    }
}

int main(int argc, char** argv) {

    // load joblist

    // CS event loop

    return 0;
}

