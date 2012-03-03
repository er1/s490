#ifndef __COMMON__
#define __COMMON__

#define PI ((double)3.141592654)

#ifdef DEBUG
#define log(...) fprintf(stderr, __VA_ARGS__)
#else
#define log(...) ;
#endif

#endif
