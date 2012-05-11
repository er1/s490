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
