#include <stdio.h> 
#include <string.h>


#include "../util.h"

int main(){

  char msg[] = "Have you ever herped so hard you derped?";
  struct derp{
    int a;
    char message[48];
    short b;
    char c;
  };

  struct derp herp;
  herp.a = 0x123456;
  strncpy(herp.message, msg, 48);
  herp.b = 1;
  herp.c = '!';

  hexDump(&herp, sizeof(struct derp)); 

  return 0; 
}


