#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#include <common/common.h>
#include <common/Packet.h>
#include <common/BlackboardConnection.h>

bool BlackboardConnection::connectBB() {
    const char* address = BB_SOCK_PATH;

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

    log("disconnect\n");

    if (bbfd >= 0)
        close(bbfd);
    bbfd = -1;
}

void BlackboardConnection::sendPacket(const Packet& buffer) {
    sendQueue.push_back(buffer);
}

/*
  This function will copy the first Packet in the recv
  queue to the reference Packet passed to it. The function
  returns true unless there were no Packets on the recv 
  queue in which case it returns false.
 */
bool BlackboardConnection::recvPacket(Packet& buffer) {
    processIncoming();
    if (recvQueue.size() == 0) {
        return false;
    }
    buffer = recvQueue.front();
    recvQueue.pop_front();
    return true;
}

void BlackboardConnection::processOutgoing() {
    log("processMsgQueue (send)\n");

    int ret;
    // send any queued outgoing packets
    while (sendQueue.size() > 0) {
        ret = send(bbfd, &(sendQueue.front().front()), sendQueue.front().size(), MSG_DONTWAIT);

        if (ret >= 0) {
            sendQueue.pop_front();
            log("sent\n");
        } else {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                break;
            } else {
                errorOnFail(FAIL, "send")
            }
        }
    }

}

void BlackboardConnection::processIncoming() {
    int ret;

    log("processMsgQueue (recv)\n");
    // attempt to get any new packets and queue them to be handled
    Packet buffer;
    while (true) {
        buffer.resize(MAX_BUFFER_SIZE);
        ret = recv(bbfd, &(buffer.front()), buffer.size(), MSG_DONTWAIT);

        if (ret == -1) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                break;
            } else {
                errorOnFail(FAIL, "recv");
                break;
            }
        }
        if (ret == 0) {
            // connection closed;
            bbfd = -1;
            break;
        }

        buffer.resize(ret);
        recvQueue.push_back(buffer);

        log("%#010x => [ ", bbfd);
        for (unsigned int i = 0; i < buffer.size(); ++i) {
            log("%02x ", buffer[i]);
        }
        log("]\n");
    }
}

/*
  This function will "flush" the send queue and "fill" the recv queue.
  This function will not block and should be periodically called in 
  and event loop. 
 */
void BlackboardConnection::processMsgQueue() {
    processOutgoing();
    processIncoming();
}

/*
  This function will block until we have some message received.
 */
void BlackboardConnection::waitForEvents() {
    fd_set fds;
    while (recvQueue.size() == 0) {
        // wait to unblock
        FD_ZERO(&fds);
        FD_SET(bbfd, &fds);
        int rv = select(bbfd + 1, &fds, NULL, NULL, NULL);

        log("returned from rv with %d\n", rv);

        if (rv == -1) {
            log("An error occurred: %d\n", errno);
        }

        //Now that we know we can safely read in the file handle, read from it and turn them into incoming messages
        processIncoming();

    }
}

int BlackboardConnection::multiWait(std::deque<BlackboardConnection*> conns, timeval* tv) {
    fd_set fds;
    int maxfd = 0;
    // wait to unblock
    FD_ZERO(&fds);

    for (std::deque<BlackboardConnection*>::const_iterator it = conns.begin(); it != conns.end(); ++it) {
        FD_SET((*it)->bbfd, &fds);
    }
    return select(maxfd + 1, &fds, NULL, NULL, tv);
}
