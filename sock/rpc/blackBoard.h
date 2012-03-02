#ifndef _SRV_H_
#define _SRV_H_

#include <cstdio>
#include <cstring>
#include <vector>
#include <map>

#include <pthread.h>

#include "csSrv.h"
#include "ksSrv.h"
#include "uiThread.h"
#include "tags.h"
#include "knowledgeItem.h"
#include "bbThread.h"

using namespace std;

//Sample knowlegeItems
#define KI_A 1
#define KI_B 2
#define KI_C 4
#define KI_D 8

//global
//extern vector<pthread_t> threadList;
extern bbThread * threadManager;

void hexDump(void * data, size_t byteLen);

#endif
