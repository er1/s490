#ifndef _POWER_H_
#define _POWER_H_

#include <sched.h>
#include <time.h>
#include <stdio.h>

#include "rtc.h"
#include "zerog_module.h" 

void power_exec();

void setSleepDuration(int seconds);

void lowPowerSleep();

short power_OK(); 

short power_check_panels(); 

#endif
