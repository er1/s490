#include "rand.h" 

// Commit

/** Seed */
void rand_init(){
  srand( time(0) ); 
}

/** To get random 8bit numbers. Mainly here so that
if we need random stuff, we can use this routine. */
uint8_t rand_get_u8() {
  uint8_t tmp = ~0; 
  return rand() % tmp; 
}

/** \see rand_get_u8 This is the same thing as that function, only that
it is for a 16 bit unsigned int. */
uint16_t rand_get_u16() {
  uint16_t tmp = ~0;
  return rand() % tmp; 
}

/** Strictly here for retrieving letters, if needed. */
uint8_t rand_ascii() {
  return 65 + (rand() % 26);  
}

