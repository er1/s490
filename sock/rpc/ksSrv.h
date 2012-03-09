#ifndef _KS_SRVT_H_
#define _KS_SRVT_H_

#include <stdint.h>
#include <pthread.h>

#include "blackboard.h"
#include "bbdef.h"

#define BUFFSIZE 256

void * handleKSConnection(void * socket);
void * runKSServer(void * arg);

#endif
