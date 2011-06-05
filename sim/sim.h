#ifndef _SIM_H_
#define _SIM_H_

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h> // For making sure certain vars are of specific size. 

//modules
#include "power.h"
#include "aocs.h"
#include "comms.h"
#include "rtc.h"
#include "zerog_module.h"

//utils
#include "rand.h" 
#include "log.h"

struct routine_t{
  int priority;
  void (*run)();
};

#endif
