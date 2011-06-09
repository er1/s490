#include <stdio.h> 

#include "../util.h"

int main(){

  char message[] = "Have you ever herped so hard you derped?";

  hexDump(message, sizeof message); 

  return 0; 
}


