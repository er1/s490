#ifndef TIMESYS_H 
#define TIMESYS_H

#include <stdint.h>
#include <stdio.h>

void timesys_init();

void timesys_exec(); 

short timesys_OK(); 

uint64_t timesys_measure();

uint64_t timesys_ground_time(); 

void timesys_edit(uint64_t); 


#endif 


