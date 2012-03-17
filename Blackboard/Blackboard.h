#ifndef BLACKBOARD_H
#define	BLACKBOARD_H

#include <stdint.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#include <deque>
#include <map>
#include <vector>

#include "bbtags.h"
#include "Packet.h"

typedef std::vector<uint8_t> DataPoint;

class KnowledgeItem {
private:
    std::deque<DataPoint> dataChain;
public:
    inline KnowledgeItem() { ksDatasource = -1; }
    inline ~KnowledgeItem() {}
    
    void update(DataPoint);

    int ksDatasource;
    std::deque<int> csListeners;

    const DataPoint getMostRecent();
    std::deque<DataPoint> getRecent(size_t);
};

class ConnectionDetails {
public:
    std::deque<KnowledgeItem*> KI;
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

    // instancing
    static Blackboard* instance;
    Blackboard();

    KnowledgeItem& getKI(bbtag);

public:
    static Blackboard* getInstance();
    void eventLoop(int);
};

#endif	/* BLACKBOARD_H */

