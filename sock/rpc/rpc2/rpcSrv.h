#ifndef _SRV_H_
#define _SRV_H_

#include <cstdio>
#include <cstring>
#include <vector>

#include <pthread.h>

#include "srvThread.h"
#include "uiThread.h"

#include "event.h"

using namespace std;

//events
#define EVENT_A 1
#define EVENT_B 2
#define EVENT_C 4
#define EVENT_D 8

//global
extern vector<pthread_t> threadList;
//extern vector<int> socketList;

#endif
