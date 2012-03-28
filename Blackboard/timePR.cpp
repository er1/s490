#include <common/common.h>
#include <common/KnowledgeSource.h>
#include <common/ControlShell.h>
#include "time.h"

KnowledgeSource myKS(BBTAG_DEMO10BOOL);
ControlShell myCS(BBTAG_SIMPLETIME);
DataPoint dp;

void update(bbtag, const DataPoint& p) {
    time_t t = p.unwrap<time_t > ();
    if (t % 20 < 10)
        dp.wrap(1);
    else
        dp.wrap(0);
    myKS.update(dp);
}

int main() {

    if ((!myCS.connectCS()) || (!myKS.connectKS())) {
        fprintf(stderr, "connection error!\n");
        exit(2);
    }

    myCS.registerCallback(update);

    std::deque<BlackboardConnection*> bbconns;
    bbconns.push_back(&myCS);
    bbconns.push_back(&myKS);

    while (true) {
        BlackboardConnection::multiWait(bbconns);
        myCS.processMsgQueue();
        myCS.checkForUpdates();
        myKS.processMsgQueue();
    }
    return 0;
}