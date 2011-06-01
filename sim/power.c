#include "power.h"

int durr;

void power_exec()
{
  printf("Power Module Executing...\n");
}

void setSleepDuration(int seconds)
{
  durr = seconds;
}

void lowPowerSleep()
{
  int sysret, now;
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = 500000;

  now = getTimeInSec();
  while (getTimeInSec() < now + 10){
    sysret = nanosleep(&ts, NULL);
    if(sysret == -1)
      perror("nanosleep()");
  }
}

