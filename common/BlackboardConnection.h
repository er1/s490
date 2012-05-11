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

#ifndef BLACKBOARDCONNECTION_H
#define	BLACKBOARDCONNECTION_H

#include <stdint.h>
#include <deque>
#include <vector>
#include <time.h>

#include "common.h"
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
    void processOutgoing();
    void processIncoming();


public:
    void processMsgQueue();
    void waitForEvents();
    
    static int multiWait(std::deque<BlackboardConnection*>, timeval* = 0);
};


#endif	/* BLACKBOARDCONNECTION_H */
