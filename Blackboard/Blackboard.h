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

#ifndef BLACKBOARD_H
#define	BLACKBOARD_H

#include <stdint.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#include <deque>
#include <map>
#include <set>
#include <vector>

#include <common/common.h>
#include <common/Packet.h>
#include "KnowledgeItem.h"

class ConnectionDetails {
public:
    std::set<KnowledgeItem*> ksList;
    std::set<KnowledgeItem*> csList;
    std::deque<Packet> sendQueue;
};

class Blackboard {
private:
    // connections and relations
    int socketListener;
    std::map<bbtag, KnowledgeItem> kiSet;
    std::map<int, ConnectionDetails> fdSet;

    // connection handling
    fd_set fd_r, fd_w, fd_x;
    int maxfd;
    timeval select_tv;

    std::deque<int> fdDeleteQueue;

    void prepareSelect();
    void handlePacket(int, const Packet&);
    void cleanClosedConnection();

    // instancing
    static Blackboard* instance;
    Blackboard();

public:
    static Blackboard* getInstance();
    void eventLoop(int);
};

#endif	/* BLACKBOARD_H */

