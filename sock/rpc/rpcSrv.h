#ifndef _SRV_H_
#define _SRV_H_

#include <cstdio>
#include <cstring>
#include <vector>

#include <pthread.h>

#include "srvThread.h"
#include "uiThread.h"

#include "knowledgeItem.h"

using namespace std;

//Sample knowlegeItems
#define KI_A 1
#define KI_B 2
#define KI_C 4
#define KI_D 8

//global
extern vector<pthread_t> threadList;

#endif
