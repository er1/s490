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
    value.resize(4);
    while (true) {
            tv.tv_sec = 0;
            tv.tv_usec = 100000;
            select(0, 0, 0, 0, &tv);
            *(uint32_t*)&value.front() = time(0);

            myKS.update(value);
    }
}
