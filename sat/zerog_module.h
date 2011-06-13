#ifndef ZEROG_MODULE_H
#define ZEROG_MODULE_H

#define ZEROG_MODE_SIMULATION 0
#define ZEROG_MODE_HARDWARE 1

#ifndef ZEROG_MODE
#define ZEROG_MODE ZEROG_MODE_SIMULATION
#endif

#include <stdint.h>
#include <stdio.h>
#include <mhash.h> 

#include "rand.h"

/** This is a module that will 'encapsulate' the functions we will be using in the simulation
with the actual code for the hardware. This is achieved by changing the compiling conditions in 
zerog_module.c to HARDWARE (TODO name might change). 
\see zerog_module.c */

void zerog_init(); 
void zerog_comms_send(char*);
char* zerog_comms_receive();
void zerog_distortion(char * data, int size); 
void zerog_cycle();
void zerog_print(); 
uint8_t zerog_get_bin_mode();
uint32_t zerog_crc32(char*,size_t); 
uint32_t zerog_get_hash(); 
uint16_t zerog_get_battery();

struct zerog_parts_t {
  /** The virtual battery. Initially set to max -> 2^16 */
  uint16_t battery; 
  /** Info for how our binary was compiled. */
  uint8_t binmode; 
  /** The last messages' hash stored in the struct. */
  uint32_t hash; 
};

#endif 


