#include "testWrite.h"

// TODO: rename semaphore to something more descriptive
void run(sem_t * semaphore)
{
	int sysret;
	int now;
	struct timespec ts;
	ts.tv_sec = 1;
	ts.tv_nsec = 0;

	puts("Test Writer...");

	while (1) {
		sem_wait(semaphore); // lock

		// do things
		puts("[Write]: W");

		sysret = nanosleep(&ts, NULL);
		if(sysret == -1)
		  perror("nanosleep()");

		sem_post(semaphore); //unlock
	}
}
