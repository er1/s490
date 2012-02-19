#include "rpcSrv.h"
#include "srvThread.h"

int event_list[] = { EVENT_A,
					 EVENT_B,
					 EVENT_C,
					 EVENT_D };

int num_events = sizeof(event_list)/sizeof(int);

void * runServer(void * arg)
{
	int s, s2, t, len;
    struct sockaddr_un local, remote;
    //char str[100];

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
        //int done, n;
        printf("Waiting for a connection...\n");
        t = sizeof(remote);
        if ((s2 = accept(s, (struct sockaddr *)&remote, (socklen_t*)&t)) == -1) {
            perror("accept");
            exit(1);
        }

        printf("Connected.\n");

		handleConnection(s2);
        close(s2);
	}
}


void handleConnection(int sockFD)
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
				
				printf("[%#X] requested event list\n", sockFD);
				//do this with the common buffer for now
				buffer[0] = OP_SEND_EVENT_LIST;
				buffer[1] = (unsigned char)num_events;
				/*int i;
				for(i=0; i<num_events; ++i)
				{
					buffer[2+i] = (unsigned char)event_list[i];
				}
				*/

				for(unsigned int i=0; i< events->size(); ++i)
				{
					printf("%d\n", (*events)[i]->id);
					buffer[2+i] = (unsigned char)(*events)[i]->id;
				}
				send(sockFD, buffer, num_events+2, 0);
			}
			else if(opcode == OP_REG_EVENT)
			{
				//8bits opcode
				//8bits event id
				//32bits addr
				read(sockFD, buffer+1, 5);
				unsigned char eId = buffer[1];
				unsigned long cbAddr = *(unsigned long *)(buffer + 2);
				printf("[%#X] requested event registration\n", sockFD);
				printf("\t event %d, addr[%#lX]\n", eId, cbAddr);

				
				for(unsigned int i=0; i< events->size(); ++i)
				{
					//check if the event is valid
					if((*events)[i]->id == eId)
					{
						//add a listener
						printf("event found...\n");
						remote_callback * rcb = new remote_callback;
						rcb->socket = sockFD;
						rcb->addr = cbAddr;
						(*events)[i]->listeners.push_back(rcb);
						printf("callback added!\n");
					}

				}
				
			}
			else
			{
				printf("invalid opcode!!!!! [%#X]\n", opcode);
			}
			
		}
	}
	
	printf("closing socket %#X\n", sockFD);
	close(sockFD);
}
