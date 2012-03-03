#ifndef _CS_H_
#define _CS_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>

#include <vector>
#include <map>

#include "bbProto.h"
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
	vector<dataPoint> * lastVect;

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
	vector<dataPoint> * getLast(uint32_t t, uint32_t n);

	static void * threadMaker(void * arg);

};

#endif
