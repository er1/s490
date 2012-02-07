#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "common.h"
#include "jobdef.h"

// create the process for a job
int job_spawn(job_instance* job) 
{
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
job_instance ** jList = 0;
int jList_cap = 0;
int jList_num = 0;

void addJob(job_instance * n)
{
	//if we are at capacity 
	//TODO optimize this
	if(jList_cap == jList_num)
		{
			int i;
			job_instance ** tmp = (job_instance *)calloc(jList_cap+8, sizeof(job_instance *));
			
			//copy everything over
			for(i=0; i<jList_cap; ++i)
				{
					tmp[i] = jList[i];
				}
			
			if(jList)
				free(jList);

			jList = tmp;
		}

	//go through the list
	int i;
	for(i=0; i<jList_cap; ++i)
		{
			//if we find a gap, add and break
			if(jList[i] == 0)
				{
					jList[i] = n;
					++jList_num;
					break; //get out of this loop!
				}
		}
}

int main() 
{
	//start with an empty list of size 8
    //jList_cap = 8;
	//jList_num = 0;
  
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
