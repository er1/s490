#include <unistd.h>
#include <fcntl.h>
#include <common/KnowledgeSource.h>

int main(int argc, char** argv) {
    int delay = 0;

    if (argc < 2) {
        fprintf(stderr, "usage: slamKS <tag> [<delay>]\n");
        exit(-1);
    }

    if (argc > 2) {
        sscanf(argv[2], "%d", &delay);
    }

    int tag;

    sscanf(argv[1], "%d", &tag);

    KnowledgeSource myks(tag);

    if (!myks.connectKS())
        exit(-1);

    int prngfd = open("/dev/zero", O_RDONLY);

    DataPoint p;
    p.resize(64);

    while (true) {
        if (delay > 0) {
            struct timeval tv;
            tv.tv_sec = delay / 1000;
            tv.tv_usec = (delay % 1000) * 1000;
            select(0, 0, 0, 0, &tv);
        }

        read(prngfd, &p.front(), p.size());
        myks.update(p);
    }

    close(prngfd);
    return 0;
}
