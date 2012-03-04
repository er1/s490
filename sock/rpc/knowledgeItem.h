#ifndef _EVENT_H_
#define _EVENT_H_

#include <vector>
#include <cstdio>
#include <pthread.h>
#include "blackBoard.h"

using namespace std;

class remote_callback
{
public:
	int socket;
	unsigned long addr;
};

class knowledgeItem
{
public:
	int id;
	vector<remote_callback *> listeners;
	int data;

	knowledgeItem();
	void addListenerOnSock(uint32_t cbA, int sock);
	void updateListeners();
	void removeListenersOnSock(int sock);
};

extern pthread_mutex_t mutex; //FIXME

extern vector<knowledgeItem *> * knowledgeItems;

#endif
