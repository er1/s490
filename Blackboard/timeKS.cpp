#include <time.h>

#include <vector>
#include <errno.h>

#include <common/common.h>
#include <common/KnowledgeSource.h>

int main(int argc, char** argv) {
    timeval tv;

    KnowledgeSource myKS(BBTAG_SIMPLETIME);
    if (!myKS.connectKS())
        exit(1);

    DataPoint value;
    time_t lastTime;
    while (true) {
        tv.tv_sec = 0;
        tv.tv_usec = 100000;
        select(0, 0, 0, 0, &tv);
        time_t t = time(0);

        if (lastTime != t) {
            value.wrap(t);
            myKS.update(value);
        }

        lastTime = t;
    }
}
