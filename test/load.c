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

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    long double a[7],b[7],loadavg;
    FILE *fp;

    sleep(1);
    fp = fopen("/proc/stat","r");
    fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&a[0],&a[1],&a[2],&a[3],&a[4],&a[5],&a[6]);
    fclose(fp);
    sleep(1);
    fp = fopen("/proc/stat","r");
    fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&b[0],&b[1],&b[2],&b[3],&b[4],&b[5],&b[6]);
    fclose(fp);

    loadavg = ((b[0]+b[1]+b[2]+b[4]+b[5]+b[6]) - (a[0]+a[1]+a[2]+a[4]+a[5]+a[6]))
         / ((b[0]+b[1]+b[2]+b[3]+b[4]+b[5]+b[6]) - (a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6]));
    printf("%Lf\n",loadavg);

    return(0);
}

