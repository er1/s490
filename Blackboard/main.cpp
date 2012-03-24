#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#include <common/common.h>
#include "Blackboard.h"

int createSocketListener(const char*);

// void pipeBurst(int) {
//     log("PIPE BURST!!!\n");
// }

int main(int argc, char** argv) {
    log("Starting... ");

    // SIGPIPE should never happen
    // if a socket fails, we will get SIGPIPE. handle it
    // log("assign action for SIGPIPE\n");
    // signal(SIGPIPE, pipeBurst);

    // get the instance of the blackboard
    Blackboard& kb = *Blackboard::getInstance();

    // get the socket to listen to blackboard requests on
    int socketListener = createSocketListener(BB_SOCK_PATH);

    // begin the event loop with the aquired socket
    log("OK!\n");
    kb.eventLoop(socketListener);

    return 0;
}

int createSocketListener(const char* address) {
    sockaddr_un local;
    int fdLocal;

    memset(&local, 0, sizeof (sockaddr_un));

    // request socket
#ifdef __APPLE__
    log("create stream socket on %s ...", address);
    exitOnFail((fdLocal = socket(AF_UNIX, SOCK_STREAM, 0)) == -1, "socket");
#else
    log("create seqpacket socket on %s ...", address);
    exitOnFail((fdLocal = socket(AF_UNIX, SOCK_SEQPACKET, 0)) == -1, "socket");
#endif

    // set socket path
    local.sun_family = AF_UNIX;
    strncpy(local.sun_path, address, sizeof (local.sun_path));

    // clear out an old socket handle if it exists
    unlink(local.sun_path);

    // bind it to our domain socket
    exitOnFail(bind(fdLocal, (sockaddr *) & local, sizeof (sockaddr_un)) == -1, "bind");

    // start accepting connections
    exitOnFail(listen(fdLocal, SOMAXCONN) == -1, "listen");

    log("success! listening as %#010x\n", fdLocal);

    return fdLocal;
}
