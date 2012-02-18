#ifndef _SRT_H_
#define _SRT_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

void handleConnection(int sockFD);
void * runServer(void *);

#endif
