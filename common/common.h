#ifndef COMMON_H
#define	COMMON_H

#include <stdint.h>
#include "bbtags.h"
#include "bbdef.h"

#include <stdlib.h>

#define PI ((double)3.141592654)

#define MAX_BUFFER_SIZE (16384)

#ifdef DEBUG
#ifndef WORDY
#define WORDY (0)
#endif
#define log(...) fprintf(stderr, __VA_ARGS__)
#else
#define WORDY (0)
#define log(...) ;
#endif

#include <stdio.h>
#define FAIL (1)
#define errorOnFail(_line, _string) if(_line){perror(_string);}
#define exitOnFail(_line, _string) if(_line){perror(_string);exit(-1);}
#define breakOnFail(_line, _string) if(_line){perror(_string);break;}

#endif	/* COMMON_H */

