#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netax25/ax25.h>

#include "../common/satdef.h"
#include "../common/common.h"
#include "../common/Packet.h"
#include "SatConnection.h"


bool SatConnection::connectSat(){
	struct full_sockaddr_ax25 sa_bind;
	struct full_sockaddr_ax25 sa_connect;
	const char* local_call = GROUND_CALLSIGN;
	const char* dest_call = SAT_CALLSIGN;
	const char* dest_call_list[] = { 0, 0 };
	dest_call_list[0] = dest_call;

	// create socket
	log("create socket\n");
	exitOnFail((satfd = socket(SAT_PROTO, SAT_PROTO_T, 0)) == -1, "socket creation");	

#ifdef  USE_AX25
	// define address
	sa_bind.fsa_ax25.sax25_family = AF_AX25;
	sa_bind.fsa_ax25.sax25_ndigis = 1;
	ax25_aton_entry(local_call, sa_bind.fsa_digipeater[0].ax25_call);
	ax25_aton_entry(local_call, sa_bind.fsa_ax25.sax25_call.ax25_call);

	sa_connect.fsa_ax25.sax25_family = AF_AX25;
	ax25_aton_arglist(dest_call_list, &sa_connect);
#endif

	// bind socket to address
	exitOnFail(bind(satfd, (struct sockaddr*)&sa_bind, sizeof(struct full_sockaddr_ax25)) == -1, "bind");

	// attempt to connect to address
	exitOnFail(connect(satfd, (struct sockaddr*)&sa_connect, sizeof(struct full_sockaddr_ax25)) != 0, "connect");

	return (satfd >= 0);
}

void SatConnection::disconnectSat(){
	log("SatConnection::disconnect\n");
	
	if(satfd >= 0)
		close satfd;

	satfd = -1;
}

void SatConnection::sendPacket(const Packet& p){
	sendQueue.push_back(p);
}

void SatConnection::processOutgoing(){
}

void SatConnection::processIncoming(){
}

void SatConnection::processMsgQueue(){
	processOutgoing();
	processIncoming();
}

void SatConnection::waitForEvents(){
}

