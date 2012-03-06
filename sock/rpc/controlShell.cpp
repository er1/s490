#include "controlShell.h"

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

	memset(&buf, 0, BUFFSIZE - 1);

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    printf("Trying to connect...\n");

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, CS_SOCK_PATH);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("connect");
        exit(1);
    }

    printf("Connected.\n");

	pthread_create(&monitor, NULL, handleConnection, (void *)NULL);

	initialized = true;
}

void controlShell::reg(uint32_t t, void * callback)
{
	//check if we have already have this callback registered
	for(map<uint32_t, void *>::iterator i=functorMap.begin(); i<functorMap.end(); ++i)
	{
		if(it->second == callback)
			return;
	}

	//dangerous assumption: we will never run out of keyspace
	++key;
	functorMap[key] = callback;

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
	
	
	dp.size = lastDP.size;
	dp.data = lastDP.data;

	lastDP.data = NULL;
	lastDP.size = 0;
	
	gotLast = false;
}

vector<dataPoint> * controlShell::getLast(uint32_t t, uint32_t n)
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
	return lastVect;
}


void * controlShell::handleConnection(void * arg)
{
	while(1)
	{
		int rcv = recv(s, buf, 1, 0);

		if(rcv < 0)
		{
			printf("read error");
			break;
		}
		else if(rcv == 0)
		{
			printf("Remote Host Closed Connection\n");
			break;
		}
		else
		{
			if(buf[0] == OP_SEND_CALLBACK)//callback
			{
				int cbid;
				dataPoint cbData;
				//get the callback id
				recv(s, buf+1, 4, 0);
				cbid = *(uint32_t *)(buf+1);
				
				//get the length of callback data
				recv(s, buf+5, 4, 0);
				cbData.size = *(uint32_t *)(buf+9);

				cbData.data = new uint8_t[cbData.size];
				recv(s, cbData.data, cbData.size, 0);
				
			}
			else
			{
				printf("invalid opcode!!!!! [%#X]\n", buf[0]);
			}
		}
	}

	close(s);
}
