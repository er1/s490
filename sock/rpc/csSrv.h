#ifndef _CS_SRVT_H_
#define _CS_SRVT_H_


#include "blackboard.h"
#include "bbdef.h"

#define BUFFSIZE 256

void * handleCSConnection(void * socket);
void * runCSServer(void * arg);

#endif
