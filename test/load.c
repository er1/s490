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

