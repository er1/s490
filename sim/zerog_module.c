#include "zerog_module.h" 

/* 
   0 -> Simulation code 
   1 -> Hardware code 
*/

#define ZEROG_COMPILE (0) 

// Code which shouldn't change on either implementation  

struct zerog_parts_t zerog_parts;

/** Return the binary mode of compilation */
uint8_t zerog_get_bin_mode(){
  return zerog_parts.binmode; 
}

/** This just prints the information of the zerog_parts struct */
void zerog_print() {
  printf("[Cube]stats : \n");
  printf("  :: Battery : %3.2f%% \n", (float) zerog_parts.battery / (uint16_t)(~0)* 100); 
}

#if ZEROG_COMPILE == 0

// Simulation Code 

/** All the initialization steps the zerog module needs to be done
should be included here. */
void zerog_init() {
  rand_init(); // Random seed for the simulation   
  zerog_parts.battery = ~0; 
  zerog_parts.binmode = 0; 
}

/** Function to send the message back to earth. This function should
connect to a BASE module */
void zerog_comms_send(char* msg){
  printf("  :: zerog :: Attempting to send message : %s", msg);
}

/** Function to receive a message from the base */
char* zerog_comms_receive(){
  // Probably have to add a distortion routine here. 
  return rand_phrase(); 
}

/** Function to perform artificial corruption of a message. Not sure
if this will be needed - cool thing to have in the simulation imo. 
This will be performed with a random bitwise operation upon bytes of 
data. */
void zerog_distortion(char* data, int size){
  //stub
  int byteCount;
  for(byteCount=0; byteCount<size; byteCount++){
    if(rand_get_u8() < 64) //lets say 25% of the time we corrupt a byte
      {
	//flip a some random bits
	data[byteCount] ^= rand_get_u8();
      }
    }
}

/** this function is to emulate a cycle at each iteration. For the 
emulation code, this will take care to generate new information for
sending or receiving and will also dissipate power from a virtual
battery. */ 
void zerog_cycle() { 
  zerog_parts.battery -= 1000; // max is 65k, so this will ensure about 65 iterations before need to recharge. 
}
#elif ZEROG_COMPILE == 1 

// Here, code specific to hardware will be put. 

/** All the initialization steps the zerog module needs to be done
should be included here. */
void zerog_init() {
  // TODO
}

#endif

