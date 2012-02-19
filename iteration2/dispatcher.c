#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "common.h"
#include "jobdef.h"

//
// Dispatcher
//
//

// TODO:
// notify process to cease running (SIGUSR1)
// kill a process under extreme condition
// recv commands through some means
// handle SIGCHLD (child dies for whatever reason)

// data structure for job instances
job_instance ** job_list = 0;
int job_list_capacity = 0;
int job_list_size = 0;

// ---- //

// create a process for a job and start it
int job_spawn(job_instance* job)
{
	pid_t pid;

	// return if null pointer
	if (job == NULL)
	{
		return JOB_ERROR;
	}
	
	// return if process exists
	if (job->running)
	{
		return JOB_SUCCESS;
	}

	// create a new process if not
	pid = vfork();

	// handle the child spawning
	if (pid == 0)
	{
		// run the new process executable
		if (job->ps_name)
		{
			char* newargv[] = { job->ps_name, NULL };
			char* newenv[] = { NULL };
			execve(job->ps_name, newargv, newenv);
		}

		// exit if a failiure occurs
		_exit(-1);
	}

	// error if new process cannot be created
	if (pid == -1)	
	{
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
int job_allow(job_instance* job)
{
	// return if null pointer
	if (job == NULL)
	{
		return JOB_ERROR;
	}

	// if the job is not running, start it, otherwise let it continue
	if (!job->running)
	{
		return job_spawn(job);
	}

	// it is running, send SIGCONT (continue)
	if (kill(job->pid, SIGCONT) != 0)
	{
		// TODO: define behavior for continue not working
		return JOB_ERROR;
	}

	return JOB_SUCCESS;
}

// hard stop a job from running
// TODO: define what happens if we have to kill a stopped job
int job_block(job_instance* job)
{
	if (job == NULL)
	{
		return JOB_ERROR;
	}

	if (!job->running)
	{
		return JOB_SUCCESS;
	}

	// send SIGSTOP (stop)
	if (kill(job->pid, SIGSTOP) != 0);
	{
		// it didn't work if we are here
		// TODO: define behavior for stop not working
		return JOB_ERROR;
	}

	return JOB_SUCCESS;
}

void job_add(job_instance * job)
{
	// no jobs defined yet? create the list and set the initial size to 1
	if (job_list == NULL)
	{
		job_list_capacity = 1;
		job_list = malloc(sizeof(job_instance) * job_list_capacity);
		// TODO: if malloc fails...
	}

	// job_list is full? resize it
	if (job_list_size == job_list_capacity)
	{
		job_list_capacity *= 2; // double makes amortized resizes in O(1)
		job_list = realloc(job_list, sizeof(job_instance) * job_list_capacity);
		// TODO: if realloc fails...
	}
}

int main() 
{
	char job_file_name[64];
	int job_file_id;
	FILE* job_file_handle;

	log("Starting up...\n");

	// open our job description file and catch is opening fails
	job_file_handle = fopen("jobs.txt", "r");
	if (!job_file_handle)
	{
		log("Failed to open jobs.txt\n");
		return -1;
	}
	
	while (1) // end of file breaks out of loop
	{
		// read job from file
		int t = fscanf(job_file_handle, "%s %d\n", job_file_name, &job_file_id);
		
		if (t == EOF)
			break;
			
		printf("Found Job [%s] with ID=%d\n", job_file_name, job_file_id);
	}
	
	log("Shutting down...\n");
	
	return 0;
}
