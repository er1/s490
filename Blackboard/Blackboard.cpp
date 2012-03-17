#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <poll.h>
#include <sys/un.h>
#include <sys/time.h>

#include "common.h"
#include "Blackboard.h"

#include "bbtags.h"
#include "bbdef.h"

Blackboard* Blackboard::instance = 0;

Blackboard::Blackboard() {
}

Blackboard* Blackboard::getInstance() {
    if (!instance)
        instance = new Blackboard;
    return instance;
}

void Blackboard::eventLoop(int _socketListener) {
    socketListener = _socketListener;
    for (;;) { // forever
        prepareSelect();

        log("\n watching %d file descriptor, %d in the cleaning queue", (unsigned int) fdSet.size(), (unsigned int) fdDeleteQueue.size());
        int selectValue = select(maxfd + 1, &fd_r, &fd_w, &fd_x, &select_tv);
        if (selectValue > 0)
            log("\nreturned %d\n", selectValue);
        else { // ok so an error occured during select..
            if (errno == EBADF) {
                log("\na connection was closed. but which one of the %d", (unsigned int) fdSet.size());
                struct pollfd fds[fdSet.size()];
                int x = 0;
                for (std::map<int, ConnectionDetails>::iterator it = fdSet.begin(); it != fdSet.end(); ++it) {
                    int fd = it->first;
                    fds[x].fd = fd;
                    fds[x].events = POLLWRNORM | POLLRDBAND;
                    x++;
                }

                int pollret = 0;
                pollret = poll(fds, x, -1);
                if (pollret >= 0) {
                    for (int y = 0; y < x; y++) {
                        if (fds[y].revents == POLLNVAL) {
                            log("\n%d was improperly closed, marking it as dirty", fds[y].fd);
                            fdDeleteQueue.push_back(fds[y].fd);
                        }
                    }
                } else {
                    log("\nCannot identify the un-properly closed socket. Crash, %d:", pollret);
                    exit(1);
                }
                cleanClosedConnection();
                continue;
            }


        }

        // if we have a new connection, accept it and add it to the fdSet
        if (FD_ISSET(socketListener, &fd_r)) {
            log("%#010x attempts connect\n", socketListener);
            int newfd = accept(socketListener, NULL, NULL);
            log("%#010x got connection %#010x\n", socketListener, newfd);

            fdSet.insert(std::pair<int, ConnectionDetails > (newfd, ConnectionDetails()));
        }

        // TODO: schedule connection handling in a more fair manner
        //              currently: lowest descriptor first

        // loop over all the connections we have and check if they need anything
        for (std::map<int, ConnectionDetails>::iterator it = fdSet.begin(); it != fdSet.end(); ++it) {
            // assign values for what we are dealing with
            int fd = it->first;
            ConnectionDetails& cd = it->second;

            // check if we can read anything (or the connection has closed (gracefully or otherwise)
            if (FD_ISSET(fd, &fd_r)) {
                log("%#010x recv\n", fd);
                Packet vecbuffer;
                vecbuffer.resize(MAX_BUFFER_SIZE, 0);
                int recvResult = recv(fd, &(vecbuffer.front()), vecbuffer.size(), 0);
                errorOnFail(recvResult < 0, "recv");

                if (recvResult > 0) {
                    vecbuffer.resize(recvResult);
                    handlePacket(fd, vecbuffer);
                } else {
                    log("%#010x close\n", fd);
                    close(fd);
                    // we cannot remove the fd from the set just yet so save it to be swept up later
                    fdDeleteQueue.push_back(fd);
                }
            }
            if (FD_ISSET(fd, &fd_w)) {
                while ((cd.sendQueue.size() > 0)) {
                    Packet& packet = cd.sendQueue.front();
                    log("%#010x send\n", fd);
                    int sendResult = send(fd, &(packet.front()), packet.size(), MSG_DONTWAIT);

                    // was data sent? if so remove it from the sent queue
                    // if not, leave it there if it would block
                    if (sendResult >= 0) {
                        cd.sendQueue.pop_front();
                    } else {
                        if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                            break;
                        } else {
                            errorOnFail(FAIL, "send")

                        }
                    }
                }
            }

            // IF any process asked to close, clean them
            cleanClosedConnection();

            // currently unused
            // if (FD_ISSET(fd, &fd_x)) {
            //     // ???
            // }
        }

        // _____________________________________________________

        // debug cpu burn prevention
        /*
        select_tv.tv_sec = 0;
        select_tv.tv_usec = 200000;
        select(0, 0, 0, 0, &select_tv);
         */
    }
}

void Blackboard::cleanClosedConnection() {
    log("\nCleaning %d connections", (unsigned int) fdDeleteQueue.size());
    for (std::deque<int>::iterator it = fdDeleteQueue.begin(); it != fdDeleteQueue.end(); ++it) {
        // fd cleanup goes here
        int fd = *it;
        ConnectionDetails details = fdSet[fd];
        log("\nCleaning connection %d", fd);
        for (std::deque<KnowledgeItem*>::iterator itKi = details.KI.begin(); itKi != details.KI.end(); ++itKi) {
            KnowledgeItem ki = *(*itKi);
            log("Resetting ki:%p to -1", &ki);
            ki.ksDatasource = -1;
        }

        fdSet.erase(fd);
    }
    fdDeleteQueue.clear();

}

void Blackboard::prepareSelect() {
    // set timeout delay for health checking
    select_tv.tv_sec = 5; // FIXME: make it configurable
    select_tv.tv_usec = 0;

    // clear old values;
    FD_ZERO(&fd_r); //set of fd for read
    FD_ZERO(&fd_w); //set of fd for write
    FD_ZERO(&fd_x); //set of fd for exceptions

    // determine which descriptors could have activity on them

    // the listener
    FD_SET(socketListener, &fd_r);
    //FD_SET(socketListener, &fd_x);
    maxfd = socketListener;

    // every other connection based on case
    for (std::map<int, ConnectionDetails>::const_iterator it = fdSet.begin(); it != fdSet.end(); ++it) {
        int fd = it->first;
        const ConnectionDetails& cd = it->second;

        // check for inbound packets
        FD_SET(fd, &fd_r); // check for inbound packets

        // if we have outbound packets, check if they can be sent
        if (cd.sendQueue.size() > 0) {
            FD_SET(fd, &fd_w);
        }

        FD_SET(fd, &fd_x); // exceptions

        if (fd > maxfd) {
            maxfd = fd;
        }
    }
}

KnowledgeItem & Blackboard::getKI(bbtag tag) {
    std::map<bbtag, KnowledgeItem>::iterator it = kiSet.find(tag);
    if (it == kiSet.end())
        kiSet.insert(std::pair<bbtag, KnowledgeItem > (tag, KnowledgeItem()));

    return kiSet.at(tag);
}

void Blackboard::handlePacket(int fd, const Packet & packet) {
    log("%#010x => [ ", fd);
    for (unsigned int i = 0; i < packet.size(); ++i) {
        log("%02x ", packet[i]);
    }
    log("]\n");

    // isolate

    Packet ret;

    switch (packet.getU32(0)) {


        case BO_CS_SUBSCRIBE_TO:
        {
            // pos     size     data
            //  0       4       COMMAND 
            //  4       4       KITAG

            log("%#010x BO_CS_SUBSCRIBE_TO requested\n", fd);

            uint32_t kiTag = packet.getU32(4);

            kiSet[kiTag].csListeners.push_back(fd);

            // TODO: send ACK

            break;
        }

        case BO_CS_GET_RECENT:
        {
            // pos     size     data
            //  0       4       COMMAND 
            //  4       4       KITAG
            //  8       4       NUMBER OF ELEMENTS
            log("%#010x BO_CS_GET_RECENT requested\n", fd);
            uint32_t kiTag = packet.getU32(4);
            uint32_t numElmnt = packet.getU32(8);
            KnowledgeItem& ki = kiSet[kiTag];

            std::deque<DataPoint> retSet = ki.getRecent(numElmnt);

            ret.resize(12);
            ret.setU32(0, BO_CS_UPDATE);
            ret.setU32(4, kiTag);
            ret.setU32(8, retSet.size());

            // find out final packet size;
            int pktSize = 0;
            for (std::deque<DataPoint>::const_iterator it = retSet.begin(); it != retSet.end(); ++it) {
                pktSize += it->size() + sizeof (uint32_t); // add datapoint size + size of datapoint size;
            }

            if (pktSize > MAX_BUFFER_SIZE) {
                log("Requested data set is too large! (%d)\n", (int) retSet.size());
            }

            // reserve space
            ret.reserve(pktSize + ret.size());


            for (std::deque<DataPoint>::const_iterator it = retSet.begin(); it != retSet.end(); ++it) {
                unsigned int lastIndex = ret.size();
                ret.resize(lastIndex + sizeof (uint32_t) + it->size());
                ret.insert(ret.end(), it->begin(), it->end());
            }

            break;
        }

        case BO_KS_SUBSCRIBE_AS:
        {
            // pos     size     data
            //  0       4       COMMAND 
            //  4       4       KITAG

            log("%#010x BO_KS_SUBSCRIBE_AS requested\n", fd);
            uint32_t kiTag = packet.getU32(4);
            KnowledgeItem& ki = kiSet[kiTag];

            // form default response packet
            ret.resize(8);
            ret.setU32(0, BO_KS_SUBSCRIPTION_FAILED);
            ret.setU32(4, kiTag);

            // attempt action and modify response  
            if (ki.ksDatasource < 0) {
                ki.ksDatasource = fd;

                log("Assigned ki:%p to fd:%d", &ki, fd);
                fdSet[fd].KI.push_back(&ki);

                ret.setU32(0, BO_KS_SUBSCRIPTION_SUCCESS);
            }

            // send packet
            fdSet[fd].sendQueue.push_back(ret);
            break;
        }

        case BO_KS_UPDATE:
        {
            // pos     size     data
            //  0       4       COMMAND 
            //  4       4       KITAG
            //  8       END     DATA      

            log("%#010x BO_KS_UPDATE requested\n", fd);
            uint32_t kiTag = packet.getU32(4);

            KnowledgeItem& ki = kiSet[kiTag];

            ret.resize(8);
            ret.setU32(0, BO_KS_UPDATE_FAILED);
            ret.setU32(4, kiTag);

            // check if we are the owner of this KI
            if (ki.ksDatasource == fd) {
                ret.setU32(0, BO_KS_UPDATE_SUCCESS);

                ki.update(DataPoint(packet.begin() + 8, packet.end()));
            }

            //Acknowledge to the KS that its update was successful
            fdSet[fd].sendQueue.push_back(ret);

            break;
        }

#ifdef DEBUG
        case BO_DEBUG_DUMP_KISET:
        {
            log("%#010x BO_DEBUG_DUMP_KISET requested\n", fd);
            for (std::map<bbtag, KnowledgeItem>::const_iterator knowledgeItemIterator = kiSet.begin(); knowledgeItemIterator != kiSet.end(); ++knowledgeItemIterator) {
                log("%d: \n", knowledgeItemIterator->first);
                std::deque<DataPoint> dp = knowledgeItemIterator->second.getRecent(5);
                for (std::deque<DataPoint>::const_iterator dataChainIterator = dp.begin(); dataChainIterator != dp.end(); ++dataChainIterator) {
                    log("[ ");
                    for (DataPoint::const_iterator dataPointIterator = dataChainIterator->begin(); dataPointIterator != dataChainIterator->end(); ++dataPointIterator) {
                        log("%02x ", *dataPointIterator);
                    }
                    log("]\n");
                }
            }
            break;
        }
#endif
        default:
            // invalid code
            log("invalid command: %d\n", packet.getU32(0));
            ;
    }


    // end isolate

    //const char* pkt = "hi";
    //fdSet[fd].sendQueue.push_back(Packet(pkt, pkt + strlen(pkt)));
}
