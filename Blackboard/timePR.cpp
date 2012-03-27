#include <common/common.h>
#include <common/KnowledgeSource.h>
#include <common/ControlShell.h>
#include "time.h"

KnowledgeSource myKS(BBTAG_DEMO10BOOL);
ControlShell myCS(BBTAG_SIMPLETIME);
DataPoint dp;

void update(bbtag, const DataPoint& p) {
    puts("!");

    time_t t = p.unwrap<time_t > ();
    if (t % 20 < 10)
        dp.wrap(1);
    else
        dp.wrap(0);
    myKS.update(dp);
}

int main() {

    puts("0");

    if (!myCS.connectCS())
        exit(1);

    puts("1");

    if (!myKS.connectKS())
        exit(2);

    puts("2");

    myCS.registerCallback(update);

    std::deque<BlackboardConnection*> bbconns;
    bbconns.push_back(&myCS);
    bbconns.push_back(&myKS);

    puts(".");


    while (true) {
        puts(">");

        BlackboardConnection::multiWait(bbconns);
        puts(".");

        myCS.processMsgQueue();
        puts(".");

        myCS.checkForUpdates();
        puts(".");

        myKS.processMsgQueue();
    }


    return 5;
}