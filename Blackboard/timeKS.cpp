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
