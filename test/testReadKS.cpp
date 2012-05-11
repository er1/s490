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
#include <math.h>

#include <common/common.h>
#include <common/KnowledgeSource.h>


struct SinePoint {
    double value;
};

int main() {
    int sysret;
    timespec ts;

    ts.tv_sec = 1;
    ts.tv_nsec = 0;

    int p;

    KnowledgeSource myKS(BBTAG_TESTREAD);

    myKS.connectKS();

    //TODO change to while(something) so we can stop it
    while (1) {
        double point;
        double t;


        // create sample
        p = (p + 27) % 1024;
        point = cos(p * PI / 512);

        SinePoint p;
        p.value = point;

        DataPoint dp;
        dp.wrap(p);
        myKS.update(dp);

        //

        printf("[Read]: ");

        for (t = -1; t < point; t += 1.0 / 32) {
            putchar(' ');
        }

        printf("+\n");


        ts.tv_sec = 0;
        ts.tv_nsec = rand() % 100 * 1000000;
        sysret = nanosleep(&ts, NULL);
        if (sysret == -1)
            perror("nanosleep()");

    }

}
