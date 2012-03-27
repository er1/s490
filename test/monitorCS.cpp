#include <common/common.h>
#include <common/ControlShell.h>

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void update(bbtag tag, const DataPoint& dp) {
    cout << tag << "\t[ ";

    for (DataPoint::const_iterator it = dp.begin(); it != dp.end(); ++it) {
        cout << (int)(*it) << ' ';
    }
    
    cout << ']' << endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "usage: monitorCS <tag>" << endl;
        exit(-1);
    }

    bbtag tag;
    sscanf(argv[1], "%d", &tag);

    ControlShell myCS(tag);
    if (!myCS.connectCS()) {
        cerr << "no bb" << endl;
        exit(-1);
    }

    myCS.registerCallback(update);

    while (true) {
        myCS.waitForEvents();
        myCS.processMsgQueue();
        myCS.checkForUpdates();
    }

    myCS.disconnectCS();

    return 0;
}

