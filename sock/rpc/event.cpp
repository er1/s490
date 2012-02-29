#include "event.h"
#include <sys/socket.h>
#include <cstring>

event::event()
{
	//derp
}

void event::addListenerOnSock(uint32_t cbA, int sock)
{
	remote_callback * rcb = new remote_callback;
	rcb->socket = sock;
	rcb->addr = cbA;

	listeners.push_back(rcb);
}

void event::updateListeners()
{
	unsigned char buf[16];
	remote_callback * rc;
	printf("update listeners...\n");
	pthread_mutex_lock(&mutex);
	for(unsigned int i = 0; i < listeners.size(); ++i)
	{
		rc = listeners[i];
		printf("callback: <event %d> %#X, %#lX\n", id, rc->socket, rc->addr);
		buf[0] = OP_SEND_CALLBACK; 
		memcpy(buf+1, &(rc->addr), 4);
		send(rc->socket, buf, 5, 0);
	}
	pthread_mutex_unlock(&mutex);
}

void event::removeListenersOnSock(int sock)
{
	pthread_mutex_lock(&mutex);
	for(vector<remote_callback *>::iterator i=listeners.begin(); i<listeners.end(); ++i)
	{
		if((*i)->socket == sock)
		{
			printf("Removing listener on socket %#X from event %d\n", sock, id);
			remote_callback * rcb = *i;
			delete rcb;
			listeners.erase(i);
		}
	}
	pthread_mutex_unlock(&mutex);
}
// FIXME Cruft from assignment 1
