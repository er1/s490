#include "event.h"

event::event()
{
	//derp
}

void event::updateListeners()
{
	remote_callback * rc;
	printf("update listeners...\n");
	for(unsigned int i = 0; i < listeners.size(); ++i)
	{
		rc = listeners[i];
		printf("<event %d> %#X, %#X\n", id, rc->socket, rc->addr);
	}
}
