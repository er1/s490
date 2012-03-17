#ifndef BLACKBOARDCONNECTION_H
#define	BLACKBOARDCONNECTION_H

#include <stdint.h>
#include <deque>
#include <vector>

#include "common.h"
#include "bbdef.h"
#include "bbtags.h"
#include "Packet.h"

class BlackboardConnection {
private:
    int bbfd;
    std::deque<Packet> recvQueue;
    std::deque<Packet> sendQueue;

protected:
    bool connectBB();
    void disconnectBB();
    void sendPacket(const Packet&);
    bool recvPacket(Packet&);
    
public:
    void updateEvents();
    void waitForEvents();
};

#endif	/* BLACKBOARDCONNECTION_H */
