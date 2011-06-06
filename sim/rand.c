#include "rand.h" 

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

/** This should return a random phrase, composed of three words, picked from
an array of 12 words. */
char* rand_phrase(){ 
  char phrase[100];
  char dict[10][10] = {
    "sheep", "flaming",
    "machine", "he-man", 
    "derp", "satan",
    "coke", "food",
    "ostrich", "PAIN"
  };

  free(strdup(phrase));

  memset(phrase, 0, sizeof(phrase)); 

  strcat(phrase, dict[rand_get_u8()%10]); 
  strcat(phrase, "_"); 
  strcat(phrase, dict[rand_get_u8()%10]); 
  strcat(phrase, "_"); 
  strcat(phrase, dict[rand_get_u8()%10]); 

  return strdup(phrase); 
}

