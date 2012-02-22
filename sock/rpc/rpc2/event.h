#ifndef _EVENT_H_
#define _EVENT_H_


#include <vector>
#include <cstdio>
#include <pthread.h>
#include "rpcSrv.h"

using namespace std;

class remote_callback
{
public:
	int socket;
	unsigned long addr;
};

class event
{
public:
	int id;
	vector<remote_callback *> listeners;

	event();
	void updateListeners();
	void removeListenersOnSock(int sock);
};

extern pthread_mutex_t mutex;

extern vector<event *> * events;

#endif
