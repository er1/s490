#ifndef _BB_DEFINE_H_
#define _BB_DEFINE_H_

///////////////////////////////
/// Control Shell Interface ///
///////////////////////////////

#define CS_SOCK_PATH           ("/tmp/bb_cs_sock")

//opcodes -- requests from client (CS to BB)
#define OP_GET_EVENT_LIST      (1)
#define OP_REG_EVENT           (2)
#define OP_GET_LAST            (4)

//opcodes -- responces to client (BB to CS)
#define OP_SEND_EVENT_LIST     (1)
#define OP_SEND_CALLBACK       (2)
#define OP_RET_LAST            (4)

////////////////////////////////
// Knowledge Source Interface //
////////////////////////////////

#define KS_SOCK_PATH           ("/tmp/bb_ks_sock")

//opcodes -- KS to BB
#define OP_REG_KS              (1)
#define OP_KS_UPDATE           (2)

//opcodes -- BB to KS
#define OP_ACK_REG             (1)
#define OP_ACK_UPDATE          (2)

#endif
