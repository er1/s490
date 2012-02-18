#ifndef _SRV_H_
#define _SRV_H_

#include <cstdio>
#include <cstring>

#include <pthread.h>

#include "srvThread.h"

#define SOCK_PATH "/tmp/rpc_sock"


//opcodes -- requests from client
#define OP_GET_EVENT_LIST 1

//opcodes -- responces to client
#define OP_SEND_EVENT_LIST 1

//events
#define EVENT_A 1
#define EVENT_B 2
#define EVENT_C 4
#define EVENT_D 8

typedef struct {
	unsigned char opcode;
	unsigned char len;
	unsigned char * event_ids;

} EVENT_LIST;

typedef struct {
	int socket;
	int addr;
} remote_callback;

#endif
