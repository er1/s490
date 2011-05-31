#include "power.h"

clock_t endwait;

void setSleepDuration(int seconds)
{
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
}

void lowPowerSleep()
{
  int sysret;
  while (clock() < endwait){
    sysret = sched_yield();
    if(sysret == -1)
      perror("sched_yield()");
  }
}
