#include <unistd.h>
#include <fcntl.h>
#include <common/KnowledgeSource.h>

int main(int argc, char** argv) {

    if (argc < 2) {
        fprintf(stderr, "usage: slamKS <tag>\n");
        exit(-1);
    }

    int tag;

    sscanf(argv[1], "%d", &tag);

    KnowledgeSource myks(tag);

    if (!myks.connectKS())
        exit(-1);

    int prngfd = open("/dev/urandom", O_RDONLY);

    DataPoint p;
    p.resize(64);

    while (true) {
        read(prngfd, &p.front(), p.size());
        myks.update(p);
    }

    close(prngfd);
    return 0;
}
