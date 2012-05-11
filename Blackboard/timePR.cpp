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

#include <common/common.h>
#include <common/KnowledgeSource.h>
#include <common/ControlShell.h>
#include "time.h"

KnowledgeSource myKS1(BBTAG_DEMO10BOOL);
KnowledgeSource myKS2(BBTAG_DEMO10BOOL + 1);

ControlShell myCS(BBTAG_SIMPLETIME);
DataPoint dp;

int last = 0;

void update(bbtag, const DataPoint& p) {
    time_t t = p.unwrap<time_t > ();
    int next = 0;
    if (t % 20 < 10) {
        next = 1;
    }
    if (next != last) {
        dp.wrap(next);
        myKS1.update(dp);
        dp.wrap(1 - next);
        myKS2.update(dp);
    }
    last = next;
}

int main() {

    if ((!myCS.connectCS()) || (!myKS1.connectKS()) || (!myKS2.connectKS())) {
        fprintf(stderr, "connection error!\n");
        exit(2);
    }

    myCS.registerCallback(update);

    std::deque<BlackboardConnection*> bbconns;
    bbconns.push_back(&myCS);
    bbconns.push_back(&myKS1);
    bbconns.push_back(&myKS2);

    while (true) {
        BlackboardConnection::multiWait(bbconns);
        myCS.processMsgQueue();
        myCS.checkForUpdates();
        myKS1.processMsgQueue();
        myKS2.processMsgQueue();
    }
    return 0;
}
