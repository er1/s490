#include <cstdio>
#include <csignal>
#include <unistd.h>

#include "common.h"
#include "bbdef.h"
#include "bbtags.h"
#include "Thread.h"
#include "Blackboard.h"

int createSocketListener(const char*);

void pipeBurst(int) {
    log("PIPE BURST!!!\n");
}

int main(int argc, char** argv) {
    log("Starting...\n");

    // if a socket fails, we will get SIGPIPE. handle it
    log("assign action for SIGPIPE\n");
    signal(SIGPIPE, pipeBurst);

    Blackboard& kb = *Blackboard::getInstance();

    log("create echo listener\n");
    int socketListener = createSocketListener(BB_SOCK_PATH);

    kb.eventLoop(socketListener);

    return 0;
}

int createSocketListener(const char* address) {
    sockaddr_un local;
    int fdLocal;

    memset(&local, 0, sizeof (sockaddr_un));

    // request socket
#ifdef __APPLE__
    log("create stream socket on %s\n", address);
    exitOnFail((fdLocal = socket(AF_UNIX, SOCK_STREAM, 0)) == -1, "socket");
#else
    log("create seqpacket socket on %s\n", address);
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

    log("success! listening on %s as %#010x\n", address, fdLocal);

    return fdLocal;
}
/*
int handleSocketListener(int local) {
    sockaddr_un remote;
    int fdLocal = local;

    memset(&remote, 0, sizeof (sockaddr_un));

    int fdRemote;
    log("%#010x listening...\n", fdLocal);
    socklen_t sizeof_sockaddr_un = sizeof (sockaddr_un);
    errorOnFail((fdRemote = accept(fdLocal, (struct sockaddr *) &remote, &sizeof_sockaddr_un)) == -1, "accept");
    log("%#010x accepted connection %#010x\n", fdLocal, fdRemote);

    return fdRemote;
}
 */
