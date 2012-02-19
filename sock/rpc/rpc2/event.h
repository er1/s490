#ifndef _EVENT_H_
#define _EVENT_H_


#include <vector>
#include <cstdio>
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
};

extern vector<event *> * events;

#endif
