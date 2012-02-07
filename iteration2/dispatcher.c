#include <stdio.h>
#include <signal.h>
#include "common.h"
#include "jobdef.h"

// allow a job to run
	// spawn a new process
	// start a paused process

// stop a job from running
	// notify process to cease running
	// force pause a process
	// kill a process under extreme condition

// recv commands through some means

//need a list of jobs
job_instance * jList;
int jList_cap = 0;
int jList_num = 0;

void addJob(job_instance * n)
{
  //go through the list
  int i;
  for(i=0; i<jList_cap; ++i)
    {
      
    }
}

int main() {
  
  //start with an empty list of size 8
  jList_cap = 8;
  jList_num = 0;
  

  //read some config that tells us what to run.
  char jName[64];
  int id = 0;
  FILE * fd = fopen("jobs.txt", "r");
  if(!fd)
    {
      printf("Failed to open jobs.txt\n");
    }

  while(1)
    {
      int t = fscanf(fd, "%s %d\n", jName, &id);
      if(t == EOF)
	break;
      
      printf("Found Job [%s] with ID=%d\n", jName, id);
    }

	log("Starting up...\n");

	log("Shutting down...\n");

	return 0;
}
