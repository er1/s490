/*
	Commonly used functions

	Author:
		Eric Chan, February 2012
*/

#include <stdio.h>
#include <time.h>


void delay(int span) {
        struct timespec ts;
        ts.tv_sec  = span / 1000000000;
        ts.tv_nsec = span % 1000000000;
        if (nanosleep(&ts, NULL) == -1)
                perror("nanosleep()");
}
