#include <stdio.h>
#include <semaphore.h>  /* Semaphore */
#include <time.h>
#include <math.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define PI (3.141592654)

void run(sem_t * semaphore);
