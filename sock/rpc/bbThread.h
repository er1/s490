#ifndef _BB_THREAD_H_
#define _BB_THREAD_H_

#include <pthread.h>
#include <vector>

class bbThread
{
	pthread_mutex_t mutex;
	vector<pthread_t> threadList;

	bbThread();

public:
	createDetached(void *(*start_routine)(void*));
	removeSelf();
};

#endif
