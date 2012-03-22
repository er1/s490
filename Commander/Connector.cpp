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
#include "Connector.h"


bool Connector::connect(const char * addr, int channel){
#ifdef  USE_AX25
	struct full_sockaddr_ax25 sa_bind;
	struct full_sockaddr_ax25 sa_connect;
	const char* local_call = GROUND_CALLSIGN; //who
	const char* dest_call = SAT_CALLSIGN; //who 
	const char* dest_call_list[] = { 0, 0 };
	dest_call_list[0] = dest_call;

	// create socket
	log("create socket\n");
	exitOnFail((linkfd = socket(PF_AX25, SOCK_SEQPACKET, 0)) == -1, "socket creation");	

	// define address
	sa_bind.fsa_ax25.sax25_family = AF_AX25;
	sa_bind.fsa_ax25.sax25_ndigis = 1;
	ax25_aton_entry(local_call, sa_bind.fsa_digipeater[0].ax25_call);
	ax25_aton_entry(local_call, sa_bind.fsa_ax25.sax25_call.ax25_call);

	sa_connect.fsa_ax25.sax25_family = AF_AX25;
	ax25_aton_arglist(dest_call_list, &sa_connect);

	// bind socket to address
	exitOnFail(bind(linkfd, (struct sockaddr*)&sa_bind, sizeof(struct full_sockaddr_ax25)) == -1, "bind");
	
	// attempt to connect to address
	exitOnFail(connect(linkfd, (struct sockaddr*)&sa_connect, sizeof(struct full_sockaddr_ax25)) != 0, "connect");
#else
	//////////////////////////////////////
	//////////For Testing ONLY////////////
	//////////////////////////////////////

	sLen =  sizeof(Server);
	cLen =  sizeof(Client);
	
	exitOnFail((linkfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0, "udp socket");
	
	memset(&Server, 0, sLen);       /* Clear struct */
	Server.sin_family = AF_INET;                  /* Internet/IP */
	Server.sin_addr.s_addr = htonl(inet_addr(addr));   /* Any IP address */
	Server.sin_port = htons(channel);       /* server port */
#endif

	return (linkfd >= 0);
}

void Connector::disconnect(){
	log("disconnect\n");
	
	if(linkfd >= 0)
		close(linkfd);

	linkfd = -1;
}

void Connector::sendPacket(const Packet& p){
	sendQueue.push_back(p);
}

void Connector::processOutgoing(){

	log("processMsgQueue (send)\n");    
    int ret;
    // send any queued outgoing packets
    while (sendQueue.size() > 0) {
#ifdef  USE_AX25
        ret = send(linkfd, &(sendQueue.front().front()), sendQueue.front().size(), MSG_DONTWAIT);
#else
		ret = sendto(linkfd, &(sendQueue.front().front()), sendQueue.front().size(), 0,
					 (struct sockaddr *) &Server,
					 sLen);
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

void Connector::processIncoming(){
	int ret;
	
	log("processMsgQueue (recv)\n");
    // attempt to get any new packets and queue them to be handled
    Packet buffer;
    while (true) {
        buffer.resize(MAX_BUFFER_SIZE);

#ifdef  USE_AX25
		ret = recv(linkfd, &(buffer.front()), buffer.size(), MSG_DONTWAIT);
#else
		ret = recv(linkfd, &(buffer.front()), buffer.size(), MSG_DONTWAIT);
		recvfrom(linkfd, &(sendQueue.front().front()), sendQueue.front().size(), 0,
				 (struct sockaddr *) &Client,
				 &cLen);
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
            linkfd = -1;
        }

        buffer.resize(ret);
        recvQueue.push_back(buffer);

		log("%#010x => [ ", linkfd);
		for (unsigned int i = 0; i < buffer.size(); ++i) {
			log("%02x ", buffer[i]);
		}
		log("]\n");
    }

}

void Connector::processMsgQueue(){
	processOutgoing();
	processIncoming();
}

void Connector::waitForEvents(){
fd_set fds;
    while (recvQueue.size() == 0) {
        // wait to unblock
        FD_ZERO(&fds);
        FD_SET(linkfd, &fds);

		int rv = select(linkfd + 1, &fds, NULL, NULL, NULL);        

        log("returned from rv with %d\n", rv);
        
        if (rv == -1) {
                log("An error occurred: %d\n", errno);
        }
        
        //Now that we know we can safely read in the file handle, read from it and turn them into incoming messages
        processIncoming();

    }
}

