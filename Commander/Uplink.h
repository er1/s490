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
