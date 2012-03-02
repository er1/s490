#ifndef _BB_THREAD_H_
#define _BB_THREAD_H_

#include <pthread.h>
#include <vector>

using namespace std;

class bbThread
{
	pthread_mutex_t mutex;
	vector<pthread_t> threadList;

public:
	bbThread();
	void createDetached(void *(*start_routine)(void*));
	void createDetached(void *(*start_routine)(void*), void *);
	void removeSelf();
};

#endif
