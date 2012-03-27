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
