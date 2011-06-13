#ifndef _CORE_H_
#define _CORE_H_H

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
#include "base_module.h" 

//utils
#include "rand.h" 
#include "log.h"
#include "util.h"

void core_start();

struct routine_t{
  int priority;
  void (*run)();
};

#endif
