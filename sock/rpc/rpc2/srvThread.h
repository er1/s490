#ifndef _SRVT_H_
#define _SRVT_H_

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

#include "rpcSrv.h"
#include "rpcProto.h"

#define BUFFSIZE 255

void * handleConnection(void * socket);
void runServer();

#endif
