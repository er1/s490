#include "zerog_module.h" 

/* 
   0 -> Simulation code 
   1 -> Hardware code 
*/

#define ZEROG_COMPILE (0) 

#if ZEROG_COMPILE == 0

// Simulation Code 

struct zerog_parts_t zerog_parts;

/** All the initialization steps the zerog module needs to be done
should be included here. */
void zerog_init() {
  rand_init(); // Random seed for the simulation   
  zerog_parts.battery = ~0; 
}

/** Function to send the message back to earth. This function should
connect to a BASE module */
void zerog_comms_send(char* msg){

}

/** Function to receive a message from the base */
char* zerog_comms_receive(){

  return "temp"; 
}

/** Function to perform artificial corruption of a message. Not sure
if this will be needed - cool thing to have in the simulation imo. 
This will be performed with a random bitwise operation upon bytes of 
data. */
void zerog_distortion(void * param){

}

#elif ZEROG_COMPILE == 1 

  // Here, code specific to hardware will be put. 

#endif
