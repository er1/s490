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

