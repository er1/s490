/*
	Commonly used functions

	Author:
		Eric Chan, February 2012
*/

#include <stdio.h>
#include <time.h>
#include <errno.h>

int delay(int span)
{
        struct timespec ts_in;
        struct timespec ts_out;
	int rspan;
	const int mult = 1000000000;
        ts_in.tv_sec  = span / mult;
        ts_in.tv_nsec = span % mult;
        if (nanosleep(&ts_in, &ts_out) == -1)
	{
		if (errno != EINTR)
		{
			perror("nanosleep()");
		}
	}
	rspan = ts_out.tv_sec * mult + ts_out.tv_nsec;
	return rspan;
}
