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
