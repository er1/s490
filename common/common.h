#ifndef COMMON_H
#define	COMMON_H

#include <stdlib.h>

#define PI ((double)3.141592654)

#define MAX_BUFFER_SIZE (4096)

#ifdef DEBUG
#define log(...) fprintf(stderr, __VA_ARGS__)
#else
#define log(...) ;
#endif

#include <stdio.h>
#define FAIL (1)
#define errorOnFail(_line, _string) if(_line){perror(_string);}
#define exitOnFail(_line, _string) if(_line){perror(_string);exit(-1);}
#define breakOnFail(_line, _string) if(_line){perror(_string);break;}

#endif	/* COMMON_H */

