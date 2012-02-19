#include "event.h"
#include <sys/socket.h>
#include <cstring>

event::event()
{
	//derp
}

void event::updateListeners()
{
	unsigned char buf[16];
	remote_callback * rc;
	printf("update listeners...\n");
	for(unsigned int i = 0; i < listeners.size(); ++i)
	{
		rc = listeners[i];
		printf("callback: <event %d> %#X, %#lX\n", id, rc->socket, rc->addr);
		buf[0] = OP_SEND_CALLBACK; 
		memcpy(buf+1, &(rc->addr), 4);
		send(rc->socket, buf, 5, 0);
	}
}
