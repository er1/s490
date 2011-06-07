#include <stdio.h> 

#include "../rand.h"
#include "../zerog_module.h"

#define NUMTRIES (10) 

int main(){
  char mess[] = "This message must be destroyed!"; 
  int i;

  rand_init();

  printf("Distortion unit test :\n");
  
  for (i=0; i<NUMTRIES; ++i){
    zerog_distortion(mess, sizeof mess);
    printf("  [%2d] Message : [%s]\n", i, mess);
  }
  return 0; 
}
