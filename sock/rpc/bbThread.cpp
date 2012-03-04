#include "bbThread.h"

bbThread::bbThread()
{
	//mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&mutex, NULL);
}

void  bbThread::createDetached(void *(*start_routine)(void*))
{
	createDetached(start_routine, (void *)NULL);
}

void  bbThread::createDetached(void *(*start_routine)(void*), void * arg)
{
	pthread_t thread;
	pthread_create(&thread, NULL, start_routine, arg);
	pthread_detach(thread);
	
	pthread_mutex_lock(&mutex);
	threadList.push_back(thread);
	pthread_mutex_unlock(&mutex);
}

void bbThread::removeSelf()
{
	pthread_t thisThread;
	thisThread = pthread_self();

	pthread_mutex_lock(&mutex);
	for(vector<pthread_t>::iterator i=threadList.begin(); i<threadList.end(); ++i)
	{
		if(*i == thisThread)
		{
			threadList.erase(i);
			break;
		}
	}
	pthread_mutex_unlock(&mutex);
}
