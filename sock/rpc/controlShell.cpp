#include "controlShell.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

controlShell::controlShell()
{
	initialized = false;
	gotLast = false;
	key = 0;
}

controlShell::controlShell(uint32_t t)
{
}

controlShell::~controlShell()
{
	//kill thread if running
	//close fd if in use
	close(s);
	pthread_join(monitor, NULL);
}

void controlShell::init()
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

	fprintf(stderr, "Trying to connect...\n");

	remote.sun_family = AF_UNIX;
	strncpy(remote.sun_path, CS_SOCK_PATH, sizeof(remote.sun_path));
	if (connect(s, (struct sockaddr *)&remote, sizeof(sockaddr_un)) == -1) {
		perror("connect");
		exit(1);
	}

	fprintf(stderr, "Connected.\n");

	pthread_create(&monitor, NULL, &controlShell::threadMaker, (void *)this);

	initialized = true;
}

void controlShell::reg(uint32_t t, void (*callback)(dataPoint *))
{
	//check if we have already have this callback registered
	for(map<uint32_t, void *>::iterator i=functorMap.begin(); i!=functorMap.end(); ++i)
	{
		if(i->second == callback)
			return;
	}

	//dangerous assumption: we will never run out of keyspace
	++key;
	functorMap[key] = (void *)callback;

	buf[0] = OP_REG_EVENT;
	*(uint32_t *)(buf+1) = t;
	*(uint32_t *)(buf+5) = key;
	send(s, buf, 9, 0);

}

void controlShell::getLast(uint32_t t, dataPoint * dp)
{
	buf[0] = OP_GET_LAST;
	*(uint32_t *)(buf+1) = t;
	*(uint32_t *)(buf+5) = 1;
	send(s, buf, 9, 0);

	//need to block on something until the monitor thread gets our data
	while(gotLast == false)
	{
		//FIXME: wasting cpu
	}
	
	
	dp->size = lastDP.size;
	dp->data = lastDP.data;

	lastDP.data = NULL;
	lastDP.size = 0;
	
	gotLast = false;
}

deque<dataPoint> * controlShell::getLast(uint32_t t, uint32_t n)
{
	buf[0] = OP_GET_LAST;
	*(uint32_t *)(buf+1) = t;
	*(uint32_t *)(buf+5) = n;
	send(s, buf, 9, 0);

	//need to block on something until the monitor thread gets our data
	while(gotLast == false)
	{
		//FIXME: wasting cpu
	}

	//got our data from monitor thread
	gotLast = false;
	fprintf(stderr, "returning lastVect %p\n", lastVect);
	return lastVect;
}

void * controlShell::threadMaker(void * arg)
{
	controlShell * cs = (controlShell *)arg;
	cs->handleConnection();
	return NULL;
}

void controlShell::handleConnection()
{
	while(1)
	{
		int rcv = recv(s, buf, 1, 0);

		if(rcv < 0)
		{
			fprintf(stderr, "read error\n");
			break;
		}
		else if(rcv == 0)
		{
			fprintf(stderr, "Remote Host Closed Connection\n");
			break;
		}
		else
		{
			if(buf[0] == OP_SEND_CALLBACK)//callback
			{				
				uint32_t cbid;
				dataPoint * cbData =  new dataPoint();
				//get the callback id
				recv(s, buf+1, 4, 0);
				cbid = *(uint32_t *)(buf+1);

				fprintf(stderr, "OP_SEND_CALLBACK %#x\n", cbid);
				
				//get the length of callback data
				recv(s, buf+5, 4, 0);
				cbData->size = *(uint32_t *)(buf+9);

				cbData->data = new uint8_t[cbData->size];
				recv(s, cbData->data, cbData->size, 0);

				//do the callbxack
				void (*f)(dataPoint *) = (void(*)(dataPoint *))functorMap[cbid];
				f(cbData);
				fprintf(stderr, "returned from cb\n");
				
				delete cbData;
				
			}
			else if(buf[0] == OP_RET_LAST)
			{
				uint32_t num;
				recv(s, buf+1, 4, 0);
				num = *(uint32_t *)(buf+1);

				fprintf(stderr, "OP_RET_LAST %d\n", num);

				//TODO: refactor this in to a single case (lastDP always set, LastVect always set)
				//simple case
				if(num == 1)
				{
					if(lastVect!=NULL)
						delete lastVect;
					lastVect = new deque<dataPoint>();

					recv(s, buf+5, 4, 0);
					lastDP.size = *(uint32_t*)(buf+5);
					lastDP.data =  new uint8_t[lastDP.size];
					recv(s, lastDP.data, lastDP.size, 0);

					lastVect->push_back(lastDP);
				}
				else
				{
					//slightly less simple case
					if(lastVect!=NULL)
						delete lastVect;
					lastVect = new deque<dataPoint>();
					fprintf(stderr, "created lastVect %p\n", lastVect);
					for(uint32_t i=0; i<num; ++i)
					{
						recv(s, buf+5, 4, 0);
						lastDP.size = *(uint32_t*)(buf+5);
						lastDP.data =  new uint8_t[lastDP.size];
						recv(s, lastDP.data, lastDP.size, 0);

						lastVect->push_back(lastDP);
					}

				}
				gotLast = true;
			}
			else
			{
				fprintf(stderr, "Control Shell recv invalid opcode!!!!! [%#x]\n", buf[0]);
			}
		}
	}

	close(s);
}
