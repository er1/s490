#ifndef _KS_SRVT_H_
#define _KS_SRVT_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>

#include "blackBoard.h"
#include "bbProto.h"

#define BUFFSIZE 255

void * handleKSConnection(void * socket);
void * runKSServer(void * arg);

#endif
