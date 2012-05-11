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
#include <common/Packet.h>

int main(int argc, char** argv) {

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
    strncpy(local.sun_path, BB_SOCK_PATH, sizeof (local.sun_path));

    exitOnFail(connect(fdLocal, (struct sockaddr *) &local, sizeof (sockaddr_un)) == -1, "connect");

    Packet p;
    p.resize(4);
    p.setU32(0, BO_DEBUG_DUMP_KISET);

    send(fdLocal, &(p.front()), p.size(), 0);

    close(fdLocal);
    return 0;
}
