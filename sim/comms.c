#include "comms.h"

// utils 
#include "rand.h"

void comms_exec()
{
  printf("Communications Module Executing...\n");

  // Check if everything is ok with circuitry! 
  if (comms_OK()){
    
    printf("  :: Comms are OK\n");

    // Try to send something to base 
    printf("  :: Attempting to send message... "); 
    if (comms_send()) {
      printf(" [DONE] \n");
    } else {
      printf(" [FAIL] \n");  
    }
    
    // Try to receive something from base 
    printf("  :: Attempting to receive messasge... ");
    if (comms_receive()) {
      printf(" [DONE] : ");
      printf("%c%c%c%c", rand_ascii(), rand_ascii(), rand_ascii(), rand_ascii()); 
      printf("\n"); 
    } else {
      printf(" [FAIL] "); 
    }

  }
  else 
    printf(" :: Comms PROBLEM!\n");
}

/** Simple routine to see if Communication circuitry is fried or not */
short comms_OK(){
  // TODO - Proper code probably has to go here :P 
  switch (rand_get_u8()%30){
    case 0: // FATAL
      return 0; 
      break;
    default: // OK
      return 1; 
      break; 
  }
  return 1; // so compiler doesn't have the chance to complain - if it does, change your compiler. 
}

/** Send a message back to base station. */
short comms_send(){
  // So this should probably 
  //   1) Send something and wait
  //   2) Double check with base that that was indeed what was sent
  
  if(rand_get_u8() > 64) // number is there for whatever reason - it's just to demo fail/succ scenarios 
    return 1; // Success 

  return 0; // Fail 
}

/** Gentlemen. ALL YOUR BASE R BELONG TO US. */
short comms_receive(){
  return 1; 
}

/** Some checking to see if message is ok. */
short comms_check(){
  return 0; // TODO 
}

