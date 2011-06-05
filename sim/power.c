#include "power.h"

int power_durr;

void power_exec()
{
  int ret; 
  printf("Power Module Executing...\n");
  
  ret = power_OK();

  if (!ret){
    printf("  :: Power Module OK \n"); 
  } else {
    perror("Problem with the power module ");
  }
}

void setSleepDuration(int seconds)
{
  power_durr = seconds;
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

/** Small routine that will check out if the power module is ok. 
\return 0 on success. Error code if not. */
unsigned short power_OK(){
  return 0;  
}