/*
	Defines for commonly used functions

	Author:
		Eric Chan, February 2012

*/

#define PI ((double)3.141592654)

#ifdef DEBUG
#define log(a) fprintf(stderr, a)
#else
#define log(a) ;
#endif

void delay(int);
