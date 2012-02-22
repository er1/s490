#ifndef _RPC_PROTO_H_
#define _RPC_PROTO_H_

#define SOCK_PATH "/tmp/rpc_sock"

//opcodes -- requests from client
#define OP_GET_EVENT_LIST 1
#define OP_REG_EVENT      2

//opcodes -- responces to client
#define OP_SEND_EVENT_LIST 1
#define OP_SEND_CALLBACK 2


#endif
