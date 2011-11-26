#include "testRead.h"

void run(sem_t * semaphore)
{
	int sysret, now;
	struct timespec ts;
	ts.tv_sec = 1;
	ts.tv_nsec = 0;

	int p;
	
	puts("Test Datareader");

	//TODO change to while(something) so we can stop it
	while (1) {
		struct timeval tv;
		double point;
		int i;
		double t;

		sem_wait(semaphore);

		// create sample
		
			p = (p + 27) % 1024;
			point = cos(p * PI / 512);

		//

		printf("[Read]: ");

		for (t = -1; t < point; t += 1.0 / 32) {
			putchar(' ');
		}

		printf("+\n");


		ts.tv_sec = 0;
		ts.tv_nsec = rand() % 100 * 1000000;
		sysret = nanosleep(&ts, NULL);
		if(sysret == -1)
			perror("nanosleep()");

		sem_post(semaphore);
	}

}
