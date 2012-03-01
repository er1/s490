#ifndef _RPC_PROTO_H_
#define _RPC_PROTO_H_

///////////////////////////////
/// Control Shell Interface ///
///////////////////////////////

#define CS_SOCK_PATH "/tmp/bb_cs_sock"

//opcodes -- requests from client
#define OP_GET_EVENT_LIST 1
#define OP_REG_EVENT      2

//opcodes -- responces to client
#define OP_SEND_EVENT_LIST 1
#define OP_SEND_CALLBACK 2

////////////////////////////////
// Knowledge Source Interface //
////////////////////////////////

#define KS_SOCK_PATH "/tmp/bb_ks_sock"

#endif
