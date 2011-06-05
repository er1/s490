#ifndef _PWR_H_
#define _PWR_H_

#include <sched.h>
#include <time.h>
#include <stdio.h>

#include "rtc.h"

void power_exec();

void setSleepDuration(int seconds);

void lowPowerSleep();

unsigned short power_OK(); 

#endif
