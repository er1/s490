#include <common/KnowledgeSource.h>
#include <common/minunit.h>
#include "unistd.h"
#include "stdio.h"

int tests_run = 0;

int tag = 42;
int delayBetweenUpdateInMs = 100;

KnowledgeSource * myKS;

DataPoint p;

static const char * test_connect() {
    bool connected = myKS->connectKS();
    mu_assert("Could not connect, BB did not allow me to register for tag", connected == true);
    return 0;
}

static const char * test_update() {
    p.resize(4);
    p[0] = 'd';
    p[1] = 'e';
    p[2] = 'r';
    p[3] = 'p';
    bool updated = myKS->update(p);
    mu_assert("update failed", updated == true);
    return 0;
}

static const char * all_tests() {
    mu_run_test(test_connect);
    mu_run_test(test_update);
    return 0;
}

int main(int argc, char** argv) {

    if (argc > 1) {
        tag = atoi(argv[1]);
    }

    if (argc > 2) {
        sscanf(argv[2], "%d", &delayBetweenUpdateInMs);
    }
    myKS = new KnowledgeSource(tag);

    const char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    myKS->disconnectKS();
    return 0;
}
// 100 ms * 1000 ns per ms;
//        usleep(delayBetweenUpdateInMs * 1000);
