#include "testJob2.h"

void run(sem_t * semaphore)
{
  int sysret, now;
  struct timespec ts;
  ts.tv_sec = 1;
  ts.tv_nsec = 500000000;

  printf("Job2 started\n");

  //TODO change to while(something) so we can stop it
  while(1){
    sem_wait(semaphore);
    printf("[Job2]: %d\n", time(NULL));
    sysret = nanosleep(&ts, NULL);
    if(sysret == -1)
      perror("nanosleep()");
    sem_post(semaphore);
  }

}
