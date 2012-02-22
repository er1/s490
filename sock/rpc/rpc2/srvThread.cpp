#include "srvThread.h"

vector<pthread_t> threadList;
vector<int> socketList;

void runServer()
{
	int s, s2, t, len;
    struct sockaddr_un local, remote;

	//ask the OS for a socket
	s = socket(AF_UNIX, SOCK_STREAM, 0);
    if(s == -1)
	{
        perror("socket");
        exit(1);
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    
	//bind it to our domain socket
	if (bind(s, (struct sockaddr *)&local, len) == -1) 
	{
        perror("bind");
        exit(1);
    }

	//start accepting connections
    if (listen(s, 4) == -1) 
	{
        perror("listen");
        exit(1);
    }

	t = sizeof(remote);
    while(1)
	{
        printf("Waiting for a connection...\n");
        if ((s2 = accept(s, (struct sockaddr *)&remote, (socklen_t*)&t)) == -1) 
		{
            perror("accept");
            exit(1);
        }
        printf("Got connection [%#X].\n", s2);

		pthread_t pt;
		threadList.push_back(pt);
		//socketList.push_back(s2);

		pthread_create(
			&threadList[threadList.size()-1],
			NULL,
			handleConnection,
			//(void *)&socketList[socketList.size()-1]
			(void *)&s2
			);
	}
}


void * handleConnection(void * socket)
{
	int sockFD;
	sockFD = *(int *)socket;

	uint8_t buffer[BUFFSIZE]; // buffer for received data
	
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
			uint8_t opcode = *buffer;

			if(opcode == OP_GET_EVENT_LIST)
			{
				
				printf("[%#X] requested event list\n", sockFD);
				//do this with the common buffer for now
				buffer[0] = OP_SEND_EVENT_LIST;
				buffer[1] = (uint8_t)events->size();

				for(unsigned int i=0; i<events->size(); ++i)
				{
					printf("%d\n", (*events)[i]->id);
					buffer[2+i] = (uint8_t)(*events)[i]->id;
				}
				send(sockFD, buffer, events->size()+2, 0);
			}
			else if(opcode == OP_REG_EVENT)
			{
				//8bits opcode
				//8bits event id
				//32bits addr
				read(sockFD, buffer+1, 5);
				uint8_t eId = buffer[1];
				uint32_t cbAddr = *(uint32_t *)(buffer + 2);
				printf("[%#X] requested event registration\n", sockFD);
				printf("\t event %d, addr[%#X]\n", eId, cbAddr);

				
				for(unsigned int i=0; i<events->size(); ++i)
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

	//we lost the connection...
	//need to remove all listeners on the socket
	for(unsigned int i=0; i<events->size(); ++i)
	{
		(*events)[i]->removeListenersOnSock(sockFD);
	}
	
	printf("closing socket %#X\n", sockFD);
	close(sockFD);

	return NULL;
}
