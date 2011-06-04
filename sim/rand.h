#ifndef RAND_H
#define RAND_H

/** 
  Some random generation routines that might come in handy. 
*/

#include <time.h>
#include <stdlib.h>
#include <stdint.h>

void rand_init();
uint8_t rand_get_u8();
uint16_t rand_get_u16(); 
uint8_t rand_ascii();

#endif 

