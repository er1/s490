#ifndef _RTC_H_
#define _RTC_H_

#include <stdio.h>
#include <stdint.h>
#include <time.h>

void rtc_exec();

int getTimeInSec();

void rtc_init();

void rtc_exec(); 

short rtc_OK(); 

uint64_t rtc_measure();

uint64_t rtc_ground_time(); 

void rtc_edit(uint64_t); 



#endif
