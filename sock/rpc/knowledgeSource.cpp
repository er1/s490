#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "common.h"
#include "bbdef.h"
#include "knowledgeSource.h"

knowledgeSource::knowledgeSource()
{
	initialized = false;
}

knowledgeSource::knowledgeSource(uint32_t t)
{
	setTag(t);
}

knowledgeSource::~knowledgeSource()
{
	close();
}

void knowledgeSource::close()
{
	if (fdSocket>0) {
		log("Request close connection");
		buf[0] = OP_CLOSE_CONNECTION;
		//uint32_t rTag = tag;

		//Tell the server that we don't care about this socket anymore so that he can gracefully close it.
		send(fdSocket, buf, sizeof(OP_CLOSE_CONNECTION), 0);

		//Wait until the server closed it before I close it
		while (int n = read(fdSocket, buf, BUFFSIZE) ) {
			if (n==0) {
				// 0 was received, the socket was closed
				shutdown(fdSocket, SHUT_WR);
				// Set the descriptor to zero
				fdSocket=0;
			}
		}

	}
}

void knowledgeSource::init()
{
	if(initialized == true)
		return;

	struct sockaddr_un remote;

	memset(&remote, 0, sizeof(sockaddr_un));
	memset(&buf, 0, BUFFSIZE);

	if ((fdSocket = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	log("Trying to connect...\n");

	remote.sun_family = AF_UNIX;
	strncpy(remote.sun_path, KS_SOCK_PATH, sizeof(remote.sun_path));
	if (connect(fdSocket, (struct sockaddr *)&remote, sizeof(sockaddr_un)) == -1) {
		perror("connect");
		exit(1);
	}

	log("Connected.\n");
	
	initialized = true;
}

void knowledgeSource::setTag(uint32_t t)
{
	tag = t;
}

void knowledgeSource::reg(const char * name)
{
	buf[0] = OP_REG_KS;
	//uint32_t rTag = tag;
	
	*(uint32_t *)(buf+1) = tag;
	strncpy((char *)buf+5, name, 200);
	send(fdSocket, buf, strlen(name)+6, 0);
}

void knowledgeSource::update(uint32_t len, uint8_t * data)
{
	buf[0] = OP_KS_UPDATE;
	*(uint32_t *)(buf+1) = tag;
	*(uint32_t *)(buf+5) = len;
	send(fdSocket, buf, 9, 0);
	send(fdSocket, data, len, 0);
}
