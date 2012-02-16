#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define BUFFSIZE 255

#define SOCK_PATH "/tmp/rpc_socket"

#define OP_GET_EVENT_LIST 1


#define EVENT_A 1
#define EVENT_B 2
#define EVENT_C 4
#define EVENT_D 8

int event_list[] = { EVENT_A,
					 EVENT_B,
					 EVENT_C,
					 EVENT_D };




void handlebars(int sockFD)
{
	unsigned char buffer[BUFFSIZE]; // buffer for received data

	memset(&buffer, 0, BUFFSIZE - 1);

	//opcode handling state machine
	while(1)
	{
		//lets try reading the op code
		printf("read opcode...\n");
		int rcv = read(sockFD, buffer, 1);

		if(rcv < 0)
		{
			perror("read error");
			break;
		}
		else if(rcv == 0)
		{
			printf("Remote Host Closed Connection\n");
			break;
		}
		else
		{
			printf("recieved %d bytes from [%#X]\n", rcv, sockFD);

			//actually handle commands
			unsigned char opcode = *buffer;

			if(opcode == OP_GET_EVENT_LIST)
			{
				//do something
				printf("[%#X] requested event list\n");
			}
			else
			{
				printf("invalid opcode!!!!! [%d]\n", opcode);
			}
			
		}
	}
	
	printf("closing socket %#X\n", sockFD);
	close(sockFD);
}

int main(void)
{
    int s, s2, t, len;
    struct sockaddr_un local, remote;
    char str[100];

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(s, (struct sockaddr *)&local, len) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(s, 1) == -1) {
        perror("listen");
        exit(1);
    }

    for(;;) {
        int done, n;
        printf("Waiting for a connection...\n");
        t = sizeof(remote);
        if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
            perror("accept");
            exit(1);
        }

        printf("Connected.\n");

/*        done = 0;
        do {
            n = recv(s2, str, 100, 0);
            if (n <= 0) {
                if (n < 0) perror("recv");
                done = 1;
            }

            if (!done) 
                if (send(s2, str, n, 0) < 0) {
                    perror("send");
                    done = 1;
                }
        } while (!done);
*/

		handlebars(s2);

        close(s2);
    }

    return 0;
}

