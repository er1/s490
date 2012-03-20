#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <deque>
#include "../common/common.h"
#include "../common/Packet.h"
#include "bbdef.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: monitorCS <socket>\n");
        return -1;
    }

    sockaddr_un local;
    int fdLocal;

    memset(&local, 0, sizeof (sockaddr_un));

    // request socket
#ifdef __APPLE__
    log("create stream socket on %s\n", argv[1]);
    exitOnFail((fdLocal = socket(AF_UNIX, SOCK_STREAM, 0)) == -1, "socket");
#else
    log("create seqpacket socket on %s\n", argv[1]);
    exitOnFail((fdLocal = socket(AF_UNIX, SOCK_SEQPACKET, 0)) == -1, "socket");
#endif

    // set socket path
    local.sun_family = AF_UNIX;
    strncpy(local.sun_path, argv[1], sizeof (local.sun_path));

    exitOnFail(connect(fdLocal, (struct sockaddr *) &local, sizeof (sockaddr_un)) == -1, "connect");

    Packet p;
    p.resize(4);
    p.setU32(0, BO_DEBUG_DUMP_KISET);

    send(fdLocal, &(p.front()), p.size(), 0);

    close(fdLocal);
    return 0;
}
