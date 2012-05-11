/*
   Copyright 2012 Corey Clayton, Eric Chan, Mathieu Dumais-Savard

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

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

