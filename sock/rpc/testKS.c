#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdint.h>

#include "bbProto.h"

#define BUFFSIZE 255

int main(void)
{
    int s, len;
    struct sockaddr_un remote;
    uint8_t buf[BUFFSIZE];

	memset(&buf, 0, BUFFSIZE - 1);

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    printf("Trying to connect...\n");

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, KS_SOCK_PATH);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("connect");
        exit(1);
    }

    printf("Connected.\n");

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
		*(uint32_t *)(buf+1) = size;
		printf("input a character:\n-->");
		scanf("%c", buf+5); //the data
		printf("\n");
		send(s, buf, 6, 0);
		
		if(*(char *)(buf+5) == 'q')
			break;
	}

	
	////////////////////////////////////

    close(s);

    return 0;
}
