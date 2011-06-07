#include <stdio.h> 
#include <stdlib.h>
#include <stdint.h> 

#include "../rand.h"

#define TRIES (1000) 

int main(){
  int i; 
  uint64_t tmp,k,j; 

  rand_init(); 

  k = 0;
  j = 0;

  printf("Random unit test:\n");
  
  printf("  Max / Min U8 : ");
  for (i=0; i<TRIES; ++i){
    tmp = rand_get_u8(); 
    if (tmp > k) 
      k = tmp;
    else if (tmp <j)
      j = tmp; 
  }
  printf("%d / %d \n", k, j);
  
  k = 0;
  j = 0; 

  printf("  Max / Min U16 : ");
  for (i=0; i<TRIES; ++i){
    tmp = rand_get_u16(); 
    if (tmp > k) 
      k = tmp;
    else if (tmp <j)
      j = tmp; 
  }
  printf("%d / %d \n", k, j);


  return 0; 
}
