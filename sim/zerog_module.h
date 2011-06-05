#ifndef ZEROG_MODULE_H
#define ZEROG_MODULE_H

#include "rand.h"

/** This is a module that will 'encapsulate' the functions we will be using in the simulation
with the actual code for the hardware. This is achieved by changing the compiling conditions in 
zerog_module.c to HARDWARE (TODO name might change). 
\see zerog_module.c */

void zerog_init(); 
void zerog_comms_send(char*);
char* zerog_comms_receive();
//void zerog_power_
void zerog_distortion(void*); 


#endif 
