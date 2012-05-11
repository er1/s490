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
