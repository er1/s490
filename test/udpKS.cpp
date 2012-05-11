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

/*
 * totally ripped of from http://www.abc.se/~m6695/udp.html with some modifications
 */
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <common/KnowledgeSource.h>

#define BUFLEN 4096

void diep(const char *s) {
    perror(s);
    exit(1);
}

int main(int argc, char** argv) {
    struct sockaddr_in si_me, si_other;
    int s;
    unsigned int slen = sizeof (si_other);

    if (argc < 2) {
        fprintf(stderr, "usage: updKS <port>\n");
        exit(-1);
    }

    int port;

    sscanf(argv[1], "%d", &port);

    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        diep("socket");

    memset((char *) &si_me, 0, sizeof (si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(port);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(s, (sockaddr*) & si_me, sizeof (si_me)) == -1)
        diep("bind");

    KnowledgeSource myks(port);

    if (!myks.connectKS())
        diep("connectKS");

    DataPoint p;

    while (true) {
        p.resize(BUFLEN);

        int ret = recvfrom(s, &p.front(), p.size(), 0, (sockaddr*) & si_other, &slen);

        if (ret < 0)
            diep("recvfrom()");

        p.resize(ret);

        myks.update(p);

    }

    close(s);
    return 0;
}
