#include <stdio.h> 
#include <string.h> 

#include "../rand.h"
#include "../zerog_module.h"

#define NUMTRIES (100) 

int main(int argc, char** argv){
  char mess[] = "This message must be destroyed!"; 
  int i;
  int j; 

  rand_init();

  printf("Distortion unit test :\n");
  printf("  Initial message of size %d: %s\n", strlen(mess), mess); 

  printf("  To do a hex dump, launch with -hex \n");
  
  if (argc > 1 && !strcmp(argv[1], "-hex")){
    for (i=0; i<NUMTRIES; ++i){
      zerog_distortion(mess, sizeof mess); 
      for (j=0; j<sizeof mess; ++j){
        printf("%8x|", mess[j]); 
      }
      printf("\n");
    }
  } else {
    for (i=0; i<NUMTRIES; ++i){
      zerog_distortion(mess, sizeof mess);
      printf("  [%2d] Message : [%s]\n", i, mess);
    }
  }
  
  return 0; 
}
