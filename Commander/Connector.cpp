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


bool SatConnection::connect(){
#ifdef  USE_AX25
	struct full_sockaddr_ax25 sa_bind;
	struct full_sockaddr_ax25 sa_connect;
	const char* local_call = GROUND_CALLSIGN;
	const char* dest_call = SAT_CALLSIGN;
	const char* dest_call_list[] = { 0, 0 };
	dest_call_list[0] = dest_call;

	// create socket
	log("create socket\n");
	exitOnFail((satfd = socket(PF_AX25, SOCK_SEQPACKET, 0)) == -1, "socket creation");	

	// define address
	sa_bind.fsa_ax25.sax25_family = AF_AX25;
	sa_bind.fsa_ax25.sax25_ndigis = 1;
	ax25_aton_entry(local_call, sa_bind.fsa_digipeater[0].ax25_call);
	ax25_aton_entry(local_call, sa_bind.fsa_ax25.sax25_call.ax25_call);

	sa_connect.fsa_ax25.sax25_family = AF_AX25;
	ax25_aton_arglist(dest_call_list, &sa_connect);

	// bind socket to address
	exitOnFail(bind(satfd, (struct sockaddr*)&sa_bind, sizeof(struct full_sockaddr_ax25)) == -1, "bind");
	
	// attempt to connect to address
	exitOnFail(connect(satfd, (struct sockaddr*)&sa_connect, sizeof(struct full_sockaddr_ax25)) != 0, "connect");
#else
	//////////////////////////////////////
	//////////For Testing ONLY////////////
	//////////////////////////////////////
	
	struct sockaddr_in benchsatServer;
	struct sockaddr_in benchsatClient;

	int sLen =  sizeof(benchsatServer);
	int cLen =  sizeof(benchsatClient);
	
	exitOnFail((satfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0, "udp socket");
	
	memset(&benchsatServer, 0, sLen);       /* Clear struct */
	benchsatServer.sin_family = AF_INET;                  /* Internet/IP */
	benchsatServer.sin_addr.s_addr = htonl(INADDR_ANY);   /* Any IP address */
	benchsatServer.sin_port = htons(TEST_PORT);       /* server port */
#endif

	return (satfd >= 0);
}

void SatConnection::disconnect(){
	log("disconnect\n");
	
	if(satfd >= 0)
		close satfd;

	satfd = -1;
}

void SatConnection::sendPacket(const Packet& p){
	sendQueue.push_back(p);
}

void SatConnection::processOutgoing(){

	log("processMsgQueue (send)\n");    
    int ret;
    // send any queued outgoing packets
    while (sendQueue.size() > 0) {
#ifdef  USE_AX25
        ret = send(satfd, &(sendQueue.front().front()), sendQueue.front().size(), MSG_DONTWAIT);
#else
		ret = sendto(satfd, &(sendQueue.front().front()), sendQueue.front().size(), 0,
					 (struct sockaddr *) &benchsatServer,
					 &sLen)) 
#endif
        if (ret >= 0) {
            sendQueue.pop_front();
            log("sent\n");
        } else {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                break;
            } else {
                errorOnFail(FAIL, "send")
            }
        }
    }


}

void SatConnection::processIncoming(){
	int ret;
	
	log("processMsgQueue (recv)\n");
    // attempt to get any new packets and queue them to be handled
    Packet buffer;
    while (true) {
        buffer.resize(MAX_BUFFER_SIZE);

#ifdef  USE_AX25
		ret = recv(bbfd, &(buffer.front()), buffer.size(), MSG_DONTWAIT);
#else
		ret = recv(bbfd, &(buffer.front()), buffer.size(), MSG_DONTWAIT);
		recvfrom(satfd, &(sendQueue.front().front()), sendQueue.front().size(), 0,
				 (struct sockaddr *) &benchsatClient,
				 &cLen)) 
#endif
      

        if (ret == -1) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                break;
            } else {
                errorOnFail(FAIL, "recv");
            }
        }
        if (ret == 0) {
            // connection closed;
            bbfd = -1;
        }

        buffer.resize(ret);
        recvQueue.push_back(buffer);

		log("%#010x => [ ", bbfd);
		for (unsigned int i = 0; i < buffer.size(); ++i) {
			log("%02x ", buffer[i]);
		}
		log("]\n");
    }


}

void SatConnection::processMsgQueue(){
	processOutgoing();
	processIncoming();
}

void SatConnection::waitForEvents(){
fd_set fds;
    while (recvQueue.size() == 0) {
        // wait to unblock
        FD_ZERO(&fds);
        FD_SET(satfd, &fds);

		int rv = select(satfd + 1, &fds, NULL, NULL, NULL);        

        log("returned from rv with %d\n", rv);
        
        if (rv == -1) {
                log("An error occurred: %d\n", errno);
        }
        
        //Now that we know we can safely read in the file handle, read from it and turn them into incoming messages
        processIncoming();

    }
}

