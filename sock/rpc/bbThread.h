#ifndef _BB_THREAD_H_
#define _BB_THREAD_H_

#include <pthread.h>
#include <set>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class bbThread
{
	pthread_mutex_t threadListMutex;
	set<pthread_t> threadList;

public:
	bbThread();
	void createDetached(void *(*start_routine)(void*), void * = NULL);
	void removeSelf();
};

#endif
