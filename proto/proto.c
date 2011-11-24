/******************************************************************
Prototype Job Manager (Incubator)

Author: Corey Clayton, November 2011

The job manager is responcible for controlling the execution of 
'Jobs' which are mostly pre-determined. A thread will exist for
the purpose of executing a Job when it is supposed to run.

For example:

The set of jobs = {A, B, C, D}

So we will have ThreadA ThreadB ThreadC ThreadD for handling
when those jobs may need to run. It is possible that only a 
subset of those are expected to run. 

The operator may decide to run only a subset {A, B} periodically
and thus the Job manager will spawn ThreadA and ThreadB and
allow them to run using semaphores. 


*******************************************************************/

#include <stdio.h>
#include <pthread.h>    /* POSIX Threads */
#include <semaphore.h>  /* Semaphore */
#include <stdlib.h>
#include <dlfcn.h>    /* Dynamic object loading */

//void testThread1(void *);
//void testThread2(void *);


int main()
{

  void * handle1; 
  void * handle2; //shared obj handles
  void (*runJ1)(sem_t *); //function pointers for imports
  void (*runJ2)(sem_t *); 

  pthread_t thread1;
  pthread_t thread2;

  sem_t s1;
  sem_t s2;

  
  printf("Started.\nLoading shared objects...");
  
  //now lets try loading the objects

  handle1 = dlopen("testJob1.so", RTLD_LAZY); //TODO: look in to which LDflag is best for us
  if(!handle1){
    fprintf (stderr, "%s\n", dlerror());
    exit(1);
  }

  handle2 = dlopen("testJob2.so", RTLD_LAZY); 
  if(!handle2){
    fprintf (stderr, "%s\n", dlerror());
    exit(1);
  }

  dlerror(); //clear any remenants

  runJ1 = dlsym(handle1, "run");
  runJ2 = dlsym(handle2, "run");

  printf(" done.\n");

  printf("initialize semaphores\n");
  
  sem_init(&s1, 0, 1);
  sem_init(&s2, 0, 1);

  printf("Spawning threads...\n");

  pthread_create(&thread1, NULL, (void *)runJ1, (void *)&s1);
  pthread_create(&thread2, NULL, (void *)runJ2, (void *)&s2);

  printf("done!\n");

  //wait? 

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  printf("Done!\n");
  return 0;
}

/*
void testThread1(void * ptr)
{
  sem_wait(&s1);
  printf("T1 reporting in\n");
  sem_post(&s1);
}

void testThread2(void * ptr)
{
  sem_wait(&s2);
  printf("T2 reporting in\n");
  sem_post(&s2);
}
*/

