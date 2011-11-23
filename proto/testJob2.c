#include "testJob2.h"

void run(sem_t * semaphore)
{
  int sysret, now;
  struct timespec ts;
  ts.tv_sec = 1;
  ts.tv_nsec = 0;

  //TODO change to while(something) so we can stop it
  while(1){
    printf("[Job2]: %d\n", getTimeInSeconds());
    sysret = nanosleep(&ts, NULL);
    if(sysret == -1)
      perror("nanosleep()");
  }

}
