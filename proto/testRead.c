#include "testRead.h"

#define DATAPATH ("data/testdata1.fifo")

void run(sem_t * semaphore)
{
	int sysret, now;
	struct timespec ts;
	struct stat filestat;

	ts.tv_sec = 1;
	ts.tv_nsec = 0;

	int p;
	
	puts("Test Datareader");

	// create relevant files
	
	// create the buffer for the data
	if (stat(DATAPATH, &filestat) == -1) {
		if (errno == EEXIST) {
			if (mkfifo(DATAPATH, 0666)) {
				perror("mkfifo");
				return;
			}
		} else {
			perror("stat");
			return;
		}
	}

	// check it still exists
	if (stat(DATAPATH, &filestat) == -1) {
		perror("stat");
		return;
	}

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
