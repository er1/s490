#ifndef _SIM_H_
#define _SIM_H_

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

//modules
#include "power.h"
#include "aocs.h"
#include "comms.h"
#include "rtc.h"

struct routine_t{
  int priority;
  void (*run)();
};

#endif
