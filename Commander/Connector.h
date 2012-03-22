#ifndef CONNECTR_H_
#define CONNECTR_H_

#include <stdint.h>
#include <deque>
#include <vector>
#include "../common/Packet.h"

class Connector {

private:
	int linkfd;
	std::deque<Packet> recvQueue;
    std::deque<Packet> sendQueue;
    std::deque<Packet> pendingReplyQueue;

	struct sockaddr_in Server;
	struct sockaddr_in Client;

	unsigned int sLen;
	unsigned int cLen;

protected:
	bool connect(const char * addr, int channel);
	void disconnect();
	void sendPacket(const Packet&);
	void processOutgoing();
	void processIncoming();

public:
	void processMsgQueue();
	void waitForEvents();
	

};

#endif
