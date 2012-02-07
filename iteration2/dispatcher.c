#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "common.h"
#include "jobdef.h"

// create the process for a job
int job_spawn(job_instance* job) {
	pid_t pid;

	// return if null pointer
	if (job == NULL) {
		return JOB_ERROR;
	}
	
	// return if process exists
	if (job->running) {
		return JOB_SUCCESS;
	}

	// create a new process if not
	pid = vfork();

	// handle the child spawning
	if (pid == 0) {
		// run the new process executable
		if (job->ps_name)
			execve(job->ps_name, NULL, NULL); // FIXME: remove NULL

		// exit if a failiure occurs
		_exit(-1);
	}

	// error if new process cannot be created
	if (pid == -1) {
		job->running = 0;
		job->pid = 0;
		return JOB_ERROR;
	}

	// set various internal state conditions
	job->running = 1;
	job->pid = pid;

	return 0;
}

// allow a job to run
int job_allow(job_instance* job) {
	if (job == NULL) {
		return JOB_ERROR;
	}

	if (!job->running) {
		job_spawn(job);
	} else {
		// send SIGCONT
	}
	return JOB_SUCCESS;
}

int job_block(job_instance* job) {
	if (job == NULL) {
		return JOB_ERROR;
	}

	if (!job->running) {
		return JOB_SUCCESS;
	}

	// SEND SIGSTOP

	return JOB_ERROR; // FIXME: BASE STOP CASE
}

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

void addJob(char * n, int id)
{
  //jList[jList_num] = 
}

int main() {
  
  //start with an empty list of size 8
  jList_cap = 8;
  //jList = ;
  

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
