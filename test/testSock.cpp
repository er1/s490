/*
   Copyright 2012 Corey Clayton, Eric Chan, Mathieu Dumais-Savard

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <deque>
#include <common/common.h>

struct simplePacket {
    int size;
    unsigned char* buffer[4096];
};

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


    std::deque<simplePacket> screenBuffer, socketBuffer;


    for (;;) {
        timeval tv;
        tv.tv_sec = 10;
        tv.tv_usec = 0;
        fd_set r;
        fd_set w;

        FD_ZERO(&r);
        FD_ZERO(&w);
        FD_SET(0, &r);
        if (screenBuffer.size()) {
            FD_SET(1, &w);
        }
        FD_SET(fdLocal, &r);
        if (socketBuffer.size()) {
            FD_SET(fdLocal, &w);
        }

        select(fdLocal + 1, &r, &w, 0, &tv);

        if (FD_ISSET(0, &r)) {
            simplePacket p;
            p.size = read(0, p.buffer, sizeof (p.buffer));
            if (!p.size) {
                break;
            }
            socketBuffer.push_back(p);
        }
        if (FD_ISSET(1, &w)) {
            simplePacket p = screenBuffer.front();
            screenBuffer.pop_front();
            write(1, p.buffer, p.size);
        }
        if (FD_ISSET(fdLocal, &r)) {
            simplePacket p;
            p.size = read(fdLocal, p.buffer, sizeof (p.buffer));
            if (!p.size) {
                break;
            }
            screenBuffer.push_back(p);
        }
        if (FD_ISSET(fdLocal, &w)) {
            simplePacket p = socketBuffer.front();
            socketBuffer.pop_front();
            write(fdLocal, p.buffer, p.size);
        }


    }

    close(0);
    close(1);
    close(fdLocal);
    return 0;
}
