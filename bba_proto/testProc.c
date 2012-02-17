#include "testProc.h"

// TODO: rename semaphore to something more descriptive
void run(sem_t * semaphore)
{
	int sysret;
	int now;
	struct timespec ts;
	ts.tv_sec = 1;
	ts.tv_nsec = 0;

	puts("Test Processor...");

	while (1) {
		sem_wait(semaphore); // lock

		// do things
		puts("[Proc]: !");

		sysret = nanosleep(&ts, NULL);
		if(sysret == -1)
		  perror("nanosleep()");

		sem_post(semaphore); //unlock
	}
}
