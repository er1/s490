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
	if(s > 0)
		close(s);
}

void knowledgeSource::init()
{
	if(initialized == true)
		return;

	struct sockaddr_un remote;

	memset(&remote, 0, sizeof(sockaddr_un));
	memset(&buf, 0, BUFFSIZE);

	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	log("Trying to connect...\n");

	remote.sun_family = AF_UNIX;
	strncpy(remote.sun_path, KS_SOCK_PATH, sizeof(remote.sun_path));
	if (connect(s, (struct sockaddr *)&remote, sizeof(sockaddr_un)) == -1) {
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
	send(s, buf, strlen(name)+6, 0);
}

void knowledgeSource::update(uint32_t len, uint8_t * data)
{
	buf[0] = OP_KS_UPDATE;
	*(uint32_t *)(buf+1) = tag;
	*(uint32_t *)(buf+5) = len;
	send(s, buf, 9, 0);
	send(s, data, len, 0);
}
