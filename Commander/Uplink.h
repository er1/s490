#ifndef UPLINK_H_
#define UPLINK_H_

#include "../common/Packet.h"
#include <deque>
#include <cstdio>

//some replicated code here...

class Uplink {
private:
    int upfd;
	unsigned int mtu_size;
	struct sockaddr_in si_other;
//    std::deque<Packet> recvQueue;
    std::deque<Packet> sendQueue;
//    std::deque<Packet> pendQueue;

public:
	Uplink();
	~Uplink();
	void send(Packet p);
	void prepareLink();
	void processOutgoing();
};


#endif //UPLINK_H_
