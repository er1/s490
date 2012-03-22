#ifndef SATCON_H_
#define SATCON_H_

#include <stdint.h>
#include <deque>
#include <vector>

class SatConnection {

private:
	int satfd;
	std::deque<Packet> recvQueue;
    std::deque<Packet> sendQueue;
    std::deque<Packet> pendingReplyQueue;

protected:
	bool connect();
	void disconnect();
	void sendPacket(const Packet&);
	void processOutgoing();
	void processIncoming();

public:
	void processMsgQueue();
	void waitForEvents();

};

#endif
