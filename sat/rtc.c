#include "rtc.h"

uint64_t RTC_TIME = 0;

int getTimeInSec()
{
  //since we have no hardware yet, just ask the system for it
  return time(NULL);
}

// These are all like unix timestamps, therefore uint64_t to store. 

/** For whatever initialization this module needs */
void rtc_init(){

}

void rtc_exec() {
  int ret; 
  ret = rtc_OK(); 

  printf("Timesys module executing ... \n");
  printf("  :: Timesys module "); 
  if(!ret) {
    printf(" [ OK ]\n");
    printf("  :: Measuring change : %llu\n", rtc_measure()); 
    printf("  :: Measuring ground time : %llu\n", rtc_ground_time());
  } else {
    printf(" [FAIL] : %d \n", ret); 
  }
}

/** Perform any checking needed to see if the module is ok */
short rtc_OK(){
  return 0; 
}

/** Measure the change in time */
uint64_t rtc_measure() {
  return 0; 
}

/** Measure what time the base station is at. */
uint64_t rtc_ground_time() {
  return 0; 
}

/** Edit the time if needed. */
void rtc_edit(uint64_t newtime) {
  RTC_TIME = newtime;  
}



