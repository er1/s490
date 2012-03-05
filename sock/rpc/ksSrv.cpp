#include "ksSrv.h"
#include "fcntl.h"

//vector<pthread_t> threadList;

void * runKSServer(void * arg)
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
    strcpy(local.sun_path, KS_SOCK_PATH);
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
		printf("Waiting for a (KS) connection...\n");
        if ((s2 = accept(s, (struct sockaddr *)&remote, (socklen_t*)&t)) == -1) 
		{
            perror("accept");
            exit(1);
        }
        printf("Got connection [%#X].\n", s2);

		threadManager->createDetached(handleKSConnection, (void *)&s2);
/*
		pthread_t pt;
		threadList.push_back(pt);

		pthread_create(
			&threadList[threadList.size()-1],
			NULL,
			handleKSConnection,

			(void *)&s2
			);
		pthread_detach(threadList[threadList.size()-1]);
*/
	}
}


void * handleKSConnection(void * socket)
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

			if(opcode == OP_REG_KS)
			{
				uint32_t rTag;

				printf("[%#X] Registering Knowledge Source\n", sockFD);				
				//read the tag
				read(sockFD, buffer, 4);
				rTag = *(uint32_t *)buffer;
				//read the string
				int pos = 4;
				while(1)
				{
					read(sockFD, buffer+pos, 1);
					if(*(uint8_t* )(buffer+pos) == 0)
						break;
					pos++;
				}
				printf("Register: %d:%s\n", rTag, buffer+4);
				//actually register
				//send reply
				buffer[0] = OP_ACK_REG;
				send(sockFD, buffer, 1, 0);
			}
			else if(opcode == OP_KS_UPDATE)
			{
				uint8_t * ksData = buffer;
				uint32_t dataSize;

				printf("[%#X] KS Update\n", sockFD);				
				//read the size
				read(sockFD, buffer, 4);
				dataSize = *(uint32_t *)buffer;
				printf("data size = %d\n", dataSize);
				//read the data
				if(dataSize < BUFFSIZE - 4)
				{
					//if we need more space
					ksData = new uint8_t[dataSize];
				}
				read(sockFD, ksData, dataSize);
				hexDump(ksData, dataSize);
				//store data

				//send reply
				buffer[0] = OP_ACK_UPDATE;
				send(sockFD, buffer, 1, 0);
			}
			else
			{
				printf("invalid opcode!!!!! [%#X]\n", opcode);
			}
		}
	}

	//we lost the connection...
	//need to remove all listeners on the socket
	for(unsigned int i=0; i<knowledgeItems->size(); ++i)
	{
		(*knowledgeItems)[i]->removeListenersOnSock(sockFD);
	}
	
	printf("closing socket %#X\n", sockFD);
	close(sockFD);

	threadManager->removeSelf();
/*
	for(vector<pthread_t>::iterator i=threadList.begin(); i<threadList.end(); ++i)
	{
		if(*i == pthread_self())
		{
			threadList.erase(i);
			break;
		}
	}
*/

	return NULL;
}
