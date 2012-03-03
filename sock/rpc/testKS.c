#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdint.h>

#include "bbdef.h"

#define BUFFSIZE 255

int main(void)
{
	int s;
	struct sockaddr_un remote;
	uint8_t buf[BUFFSIZE];

	memset(&remote, 0, sizeof(struct sockaddr_un));
	memset(&buf, 0, BUFFSIZE);

	if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	fprintf(stderr, "Trying to connect...\n");

	remote.sun_family = AF_UNIX;
	strncpy(remote.sun_path, KS_SOCK_PATH, sizeof(remote.sun_path));
	if (connect(s, (struct sockaddr *)&remote, sizeof(struct sockaddr_un)) == -1) {
		perror("connect");
		exit(1);
	}

	fprintf(stderr, "Connected.\n");

	//this is like a test case
	////////////////////////////////////
	buf[0] = 0;
	send(s, buf, 1, 0);
	//server gets invalid opcode
	////////////////////////////////////

	//now test registering KS
	////////////////////////////////////
	buf[0] = OP_REG_KS;
	uint32_t tag = 42;
	char ksName[] = "Test Data";
	
	*(uint32_t *)(buf+1) = tag;
	strncpy((char *)buf+5, ksName, 200);
	send(s, buf, strlen(ksName)+6, 0);
	////////////////////////////////////

	//now try sending data
	////////////////////////////////////
	while(1)
	{
		uint32_t size = 1; //size of data in bytes
		buf[0] = OP_KS_UPDATE;
		*(uint32_t *)(buf+1) = tag;
		*(uint32_t *)(buf+5) = size;
		fprintf(stderr, "input a character:\n-->");
		scanf("%c", buf+9); //the data
		fprintf(stderr, "\n");
		send(s, buf, 10, 0);
		
		if(*(char *)(buf+9) == 'q')
			break;
	}

	
	////////////////////////////////////

	close(s);

	return 0;
}
