#ifndef BLACKBOARDCONNECTION_H
#define	BLACKBOARDCONNECTION_H

#include <stdint.h>
#include <deque>
#include <vector>

#include "bbdef.h"
#include "bbtags.h"

class BlackboardConnection {
private:
    int bbfd;
    std::deque<Packet> recvQueue;
    std::deque<Packet> sendQueue;

protected:
    void sendPacket(const Packet&);
    bool recvPacket(Packet&);
    
public:
    bool connectBB(const char*);
    void disconnectBB();
    void updateEvents();
    void waitForEvents();
};

#endif	/* BLACKBOARDCONNECTION_H */
