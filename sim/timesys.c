#include "timesys.h"

// These are all like unix timestamps, therefore uint64_t to store. 

uint64_t TIMESYS_TIME = 0;

/** For whatever initialization this module needs */
void timesys_init(){

}

void timesys_exec() {
  int ret; 
  ret = timesys_OK(); 

  printf("Timesys module executing ... \n");
  printf("  :: Timesys module "); 
  if(!ret) {
    printf(" [ OK ]\n");
    printf("  :: Measuring change : %llu\n", timesys_measure()); 
    printf("  :: Measuring ground time : %llu\n", timesys_ground_time());
  } else {
    printf(" [FAIL] : %d \n", ret); 
  }
}

/** Perform any checking needed to see if the module is ok */
short timesys_OK(){
  return 0; 
}

/** Measure the change in time */
uint64_t timesys_measure() {
  return 0; 
}

/** Measure what time the base station is at. */
uint64_t timesys_ground_time() {
  return 0; 
}

/** Edit the time if needed. */
void timesys_edit(uint64_t newtime) {
  TIMESYS_TIME = newtime;  
}

