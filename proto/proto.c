/******************************************************************
Prototype Job Manager (Incubator)

Author: Corey Clayton, November 2011
        Eric Chan, November 2011

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
#include <stdlib.h>
#include <pthread.h>   /* POSIX Threads */
#include <semaphore.h> /* Semaphore */
#include <dlfcn.h>     /* Dynamic object loading */

int main()
{
	// shared object handles
	void * handleRead;
	void * handleProc;
	void * handleWrite;

	// function pointers for imports
	void (*runRead)(sem_t *);
	void (*runProc)(sem_t *);
	void (*runWrite)(sem_t *);

	// threads
	pthread_t threadRead;
	pthread_t threadProc;
	pthread_t threadWrite;

	// semaphores
	sem_t semRead;
	sem_t semProc;
	sem_t semWrite;

	puts("Started");
	puts("Loading shared objects...");
	
	// TODO: probably make into a function...
	// load reader
	handleRead = dlopen("testRead.so", RTLD_LAZY); //TODO: look in to which LDflag is best for us
	if (!handleRead) {
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}

	// load processor
	handleProc = dlopen("testProc.so", RTLD_LAZY); //TODO: look in to which LDflag is best for us
	if (!handleProc) {
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}

	// load writer
	handleWrite = dlopen("testWrite.so", RTLD_LAZY); //TODO: look in to which LDflag is best for us
	if (!handleWrite) {
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}

	// clear any other potential loader errors
	dlerror();

	runRead = dlsym(handleRead, "run");
	runProc = dlsym(handleProc, "run");
	runWrite = dlsym(handleWrite, "run");

	puts("done!");

	puts("initialize semaphores...");

	sem_init(&semRead, 0, 1);
	sem_init(&semProc, 0, 1);
	sem_init(&semWrite, 0, 1);

	puts("spawning threads...");

	pthread_create(&threadRead, NULL, (void *)runRead, &semRead);
	pthread_create(&threadProc, NULL, (void *)runProc, &semProc);
	pthread_create(&threadWrite, NULL, (void *)runWrite, &semWrite);

	puts("done!");

	//wait? 

	pthread_join(threadRead, NULL);
	pthread_join(threadProc, NULL);
	pthread_join(threadWrite, NULL);

	puts("complete!");
	return 0;
}
