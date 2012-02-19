#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "rpc.h"

#define BUFFSIZE 255

int main(void)
{
    int s, t, len;
    struct sockaddr_un remote;
    unsigned char buf[BUFFSIZE];

	memset(&buf, 0, BUFFSIZE - 1);

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    printf("Trying to connect...\n");

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCK_PATH);
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

	////////////////////////////////////
	buf[0] = 1;
	send(s, buf, 1, 0);
	//sent request for event list

	//try to recieve that
	read(s, buf, 2);
	printf("[%#X][%#X]...\n", buf[0], buf[1]);
	read(s, buf+2, buf[1]);
	printf("[%#X][%#X][%#X][%#X][%#X][%#X]...\n",
		   buf[0], buf[1],
		buf[2], buf[3], buf[4], buf[5]);

	//now try to register for something
	buf[0] = 2;
	buf[1] = 1;
	*(unsigned long*)(buf+2) = 0x12345678;
	send(s, buf, 6, 0);


/*	buf[0] = 1;
	send(s, buf, 1, 0);

	buf[0] = 2;
	send(s, buf, 1, 0);

	buf[0] = 3;
	send(s, buf, 1, 0);
	

/*    while(printf("> "), fgets(str, 100, stdin), !feof(stdin)) {
        if (send(s, str, strlen(str), 0) == -1) {
            perror("send");
            exit(1);
        }

        if ((t=recv(s, str, 100, 0)) > 0) {
            str[t] = '\0';
            printf("echo> %s", str);
        } else {
            if (t < 0) perror("recv");
            else printf("Server closed connection\n");
            exit(1);
        }
		}*/

    close(s);

    return 0;
}
