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

public:    
    bool connectBB(const char*);
    void disconnectBB();
    void sendpacket(const Packet&);
    bool recvpacket(Packet&);
    void performEvents();
};

#endif	/* BLACKBOARDCONNECTION_H */
