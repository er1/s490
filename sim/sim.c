#include "sim.h"

//main entry point
int main(int argc, char ** argv)
{
  
  // Generate seed - this should probably be removed from the end product :P 
  rand_init(); 
  // END Generate seed 

  //first activation
  if(argc > 1 && !strncmp(argv[1], "-launch", 7))
    {
      printf("Launch condition\n");
    }

  //set up the modules
  struct routine_t * schedule[8];
  memset(schedule, 0, sizeof(schedule));

  schedule[0] = malloc(sizeof(struct routine_t));
  schedule[1] = malloc(sizeof(struct routine_t));
  schedule[2] = malloc(sizeof(struct routine_t));
  schedule[3] = malloc(sizeof(struct routine_t));

  schedule[0]->run = comms_exec;
  schedule[1]->run = power_exec;
  schedule[2]->run = aocs_exec;
  schedule[3]->run = rtc_exec;

  //super simple scheduler - NOTE : I'm reducing this for the momment. 
  setSleepDuration(1);

  while(1){
    int cSched;
    lowPowerSleep();
    printf("Beep!\n");
    for(cSched=0; cSched<8; cSched++){
      if(schedule[cSched])
	schedule[cSched]->run();
    }
    setSleepDuration(10);
  }

  return 0;
}
