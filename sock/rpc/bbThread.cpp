#include "bbthread.h"

bbThread::bbThread()
{
	mutex = PTHREAD_MUTEX_INITIALIZER;
}

bbThread::createDetached(void *(*start_routine)(void*))
{
	pthread_t thread;
	pthread_create(&thread, NULL, start_routine, (void *)NULL);
	pthread_detach(&thread);
	
	pthread_mutex_lock(&mutex);
	threadList.push_back(thread);
	pthread_mutex_unlock(&mutex);
}

bbthread::removeSelf()
{
	pthread_t thisThread;
	thisThread = pthread_self();

	pthread_mutex_lock(&mutex);
	for(vector<pthread_t>::iterator i=threadList.begin(); i<threadList.end(); ++i)
	{
		if(*i == pthread_self())
		{
			threadList.erase(i);
			break;
		}
	}
	pthread_mutex_unlock(&mutex);
}
