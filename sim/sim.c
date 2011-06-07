#include "sim.h"

//main entry point
int main(int argc, char ** argv)
{
  
  zerog_init(); 
  printf("zerog module in ");
  switch(zerog_get_bin_mode()){
    case 0:  printf("emulation mode\n"); break;
    case 1:  printf("hardware mode\n"); break; 
    default: printf("phngui mgwlnafh Cthulhu Rlyeh wgahnagl fhtang\n");
  }

  char mess[] = "hello";

  zerog_distortion(mess, sizeof mess); 
  printf("%d : %s", sizeof mess, mess);

  //first activation
  if(argc > 1 && !strncmp(argv[1], "-launch", 7))
    {
      printf("Launch condition\n");
      log_message("Satelite has been launched.\n");
    }

  //set up the modules
  struct routine_t * schedule[8];
  memset(schedule, 0, sizeof(schedule));

  schedule[0] = malloc(sizeof(struct routine_t));
  schedule[1] = malloc(sizeof(struct routine_t));
  schedule[2] = malloc(sizeof(struct routine_t));
  schedule[3] = malloc(sizeof(struct routine_t));
  schedule[4] = malloc(sizeof(struct routine_t));

  schedule[0]->run = comms_exec;
  schedule[1]->run = power_exec;
  schedule[2]->run = aocs_exec;
  schedule[3]->run = rtc_exec;
  schedule[4]->run = timesys_exec;

  //super simple scheduler - NOTE : I'm reducing this for the momment. 
  setSleepDuration(1);

  while(1){
    int cSched;
    printf("\n");
    zerog_print();
    lowPowerSleep();
    printf("Beep!\n");
    for(cSched=0; cSched<8; cSched++){
      if(schedule[cSched])
	schedule[cSched]->run();
    }
    zerog_cycle(); 
    setSleepDuration(10);
  }

  return 0;
}


