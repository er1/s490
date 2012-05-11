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

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

#include "../common/satdef.h"
#include "Uplink.h"

Uplink::Uplink(){
	printf("Creating Upling Object\n");
	mtu_size = 256;
}

Uplink::~Uplink(){
	if(upfd > 0)
		close(upfd);
}

void Uplink::prepareLink(){
	printf("prepareLink called\n");
	//set up udp for testing
	upfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(TEST_PORT);
	inet_aton(TEST_IP, &si_other.sin_addr);
	
}

void Uplink::send(Packet p){
	//just add it to the send queue
	sendQueue.push_back(p);
}

void Uplink::processOutgoing(){
	printf("Processing outbound Packets...\n");

	int ret;
	while( sendQueue.size() > 0 ){
		printf("\tsendQueue has %d Packets\n", sendQueue.size());
		//TODO:packets <= MTU
		Packet p = sendQueue.front();
		printf("\t\tSending packet with size=%d\n", p.size());
		ret = sendto(upfd, &(p.front()), p.size(), 0, (sockaddr*)&si_other, sizeof(si_other));
		
		printf("sendto returned %d\n", ret);
		sendQueue.pop_front();
	}
	printf("Done with outbound Packets!\n");
	
}
