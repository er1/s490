#include "KnowledgeSource.h"
#include "BlackboardConnection.h"
#include "unistd.h"

int main(int argc, char** argv) {

    int tag = 42;
    if (argc > 1){
        tag = atoi(argv[1]);
    }
    int delayBetweenUpdateInMs = 100;
    if (argc > 2){
        delayBetweenUpdateInMs = atoi(argv[2]);
    }
    KnowledgeSource myKS(tag);

    if (myKS.connectKS()) {
        log("connected\n");
    } else {
        log("Could not connect, BB did not allow me to register for tag %d\n", tag);
        return 1;
    }

    DataPoint p;
    p.resize(4);

    while (argc > 2) {

        p[0] = 'd';
        p[1] = 'e';
        p[2] = 'r';
        p[3] = 'p';
        if (myKS.update(p)) {
            log("updated with ack\n");
        } else {
            log("update failed");
        }

        // 100 ms * 1000 ns per ms;
        usleep(delayBetweenUpdateInMs * 1000);
    }

    myKS.disconnectKS();

    return 0;
}

