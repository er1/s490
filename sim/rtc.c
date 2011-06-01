#include "rtc.h"

void rtc_exec()
{
  printf("Real Time Clock Module Executing...\n");
}

int getTimeInSec()
{
  //since we have no hardware yet, just ask the system for it
  return time(NULL);
}
