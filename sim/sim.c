#include "sim.h"

//main entry point
int main(int argc, char ** argv)
{
  //first activation
  if(argc > 1 && !strncmp(argv[1], "-launch", 7))
    {
      printf("Launch condition\n");
    }

  //super simple scheduler
  setSleepDuration(10);

  while(1){
    lowPowerSleep();
    printf("Beep!\n");
    setSleepDuration(10);
  }

  return 0;
}
