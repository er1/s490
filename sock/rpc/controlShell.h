#ifndef _CS_H_
#define _CS_H_

#include <stdint.h>
#include <pthread.h>

#include <deque>
#include <map>

#include "bbdef.h"
#include "knowledgeItem.h"

#define BUFFSIZE 256

class controlShell
{
private:
	int s;
	uint32_t key;
	uint8_t buf[BUFFSIZE];
	bool initialized;

	bool gotLast;
	dataPoint lastDP;
	deque<dataPoint> * lastVect;

	pthread_t monitor;
	pthread_mutex_t mutex; //TODO: examine if we need this
	map<uint32_t, void *> functorMap;
	
	void handleConnection();

public:
	controlShell();
	controlShell(uint32_t t);//does this make sense
	~controlShell();
	void init();
	void reg(uint32_t t, void (*callback)(dataPoint *));
	void getLast(uint32_t t, dataPoint * dp);
	deque<dataPoint> * getLast(uint32_t t, uint32_t n);

	static void * threadMaker(void * arg);

};

#endif
