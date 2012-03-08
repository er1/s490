#include "bbThread.h"

bbThread::bbThread()
{
	//mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(&mutex, NULL);
}

void  bbThread::createDetached(void *(*start_routine)(void*), void * arg)
{
	pthread_t thread;

	if (pthread_create(&thread, NULL, start_routine, arg) != 0)
	{
		perror("bbThread: pthread_create");
		exit(1);
	}

	if (pthread_detach(thread) != 0)
	{
		perror("bbThread: pthread_detach");
		exit(1);
	}

	// add this thread id to the list of active threads
	pthread_mutex_lock(&mutex);
	threadList.insert(thread);
	pthread_mutex_unlock(&mutex);
}

void bbThread::removeSelf()
{
	// get this thread id
	pthread_t thisThread;
	thisThread = pthread_self();

	// remove this thread id from the list of active threads
	pthread_mutex_lock(&mutex);
	set<pthread_t>::iterator it = threadList.find(thisThread);
	if (it != threadList.end())
	{
		threadList.erase(it);
	}
	pthread_mutex_unlock(&mutex);

	// kill off this thread
	pthread_exit(0);
}
