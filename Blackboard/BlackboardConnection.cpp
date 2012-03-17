#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#include "common.h"
#include "Packet.h"
#include "BlackboardConnection.h"

bool BlackboardConnection::connectBB(const char* address) {
    sockaddr_un local;

    memset(&local, 0, sizeof (sockaddr_un));

    // request socket
#ifdef __APPLE__
    log("create stream socket on %s\n", address);
    exitOnFail((bbfd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1, "socket");
#else
    log("create seqpacket socket on %s\n", address);
    exitOnFail((bbfd = socket(AF_UNIX, SOCK_SEQPACKET, 0)) == -1, "socket");
#endif

    // set socket path
    local.sun_family = AF_UNIX;
    strncpy(local.sun_path, address, sizeof (local.sun_path));

    exitOnFail(connect(bbfd, (sockaddr*) & local, sizeof (sockaddr_un)) == -1, "connect");
    return (bbfd >= 0);
}

void BlackboardConnection::disconnectBB() {
    // TODO: clear buffers, we assume at this point, they are empty

    if (bbfd >= 0)
        close(bbfd);
    bbfd = -1;
}

void BlackboardConnection::sendpacket(const Packet& buffer) {
    sendQueue.push_back(buffer);
}

bool BlackboardConnection::recvpacket(Packet& buffer) {
    buffer = recvQueue.front();
    recvQueue.pop_front();
    return true;
}

void BlackboardConnection::performEvents() {
    int ret;
    // send any queued outgoing packets
    while (sendQueue.size() > 0) {
        ret = send(bbfd, &(sendQueue.front()), sendQueue.front().size(), MSG_DONTWAIT);

        if (ret >= 0) {
            sendQueue.pop_front();
        } else {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                break;
            } else {
                errorOnFail(FAIL, "send")
            }
        }
    }

    // attempt to get any new packets and queue them to be handled
    Packet buffer;
    while (true) {
        buffer.resize(MAX_BUFFER_SIZE);
        ret = recv(bbfd, &(sendQueue.front()), sendQueue.front().size(), MSG_DONTWAIT);

        if (ret == -1) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                break;
            } else {
                errorOnFail(FAIL, "recv");
            }
        }
        if (ret == 0) {
            // connection closed;
            bbfd = -1;
        }

        buffer.resize(ret);
        recvQueue.push_back(buffer);
    }
}