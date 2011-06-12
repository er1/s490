#include "power.h"
#include "zerog_module.h" 

int power_durr;

// We can use these in order to set certain scenarios when the satelite reaches (hopefully not) 
// these levels. 
unsigned char power_battery_warn = 50; 
unsigned char power_battery_critical = 10; // %

void power_exec()
{
  int ret; 
  printf("Power Module Executing...\n");
  
  ret = power_OK();

  if (!ret){
    printf("  :: Power Module OK \n"); 
  } else {
    perror("Problem with the power module. Error: ");
    switch(ret){
      case 1: perror("[WARN] : Low Batteries\n"); break; 
      case 2: perror("[CR!T] : VERY LOW BATTERIES\n"); break; 
      case 3: perror("[WHAT] : Unreachable code reached\n"); break; 
    }
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
  while (getTimeInSec() < now + 1){
    sysret = nanosleep(&ts, NULL);
    if(sysret == -1)
      perror("nanosleep()");
  }
}

/** Small routine that will check out if the power module is ok. 
This is a good place to add different scenarios to take on 
different 'ohnoes' levels. 
\return 0 on success. Error code if not. 
  - 0 ok 
  - 1 warn
  - 2 critical 
TODO 
  maybe percentages should be handled from a routine 
*/
short power_OK(){ 
  if ((float)zerog_get_battery() / (uint16_t)(~0) * 100 < power_battery_critical) 
    return 2; 
  else if ((float)zerog_get_battery() / (uint16_t)(~0) * 100 < power_battery_warn)
    return 1; 
  else 
    return 0;  

  // This should (hopefully) be unreachable 
  return 3; 
}

/** This is a routine that will check whether the panels are working
properly or not. 
TODO would be nice to have a scenario that this fails, and this module
must act accordingly to save power. */
short power_check_panels() {
  return 0;
}

