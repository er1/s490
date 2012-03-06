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

#include "bbProto.h"
#include "knowledgeSource.h"

#define BUFFSIZE 256

class controlShell
{
private:
	int s;
	uint32_t key;
	uint8_t buf[BUFFSIZE];
	bool initialized;

	pthread_t monitor;
	pthread_mutex_t mutex; //TODO: examine if we need this
	map<uint32_t, void *> functorMap;
	
	void * handleConnection(void * arg);

public:
	controlShell();
	controlShell(uint32_t t);
	void init();
	void reg(uint32_t t, void * callback);
	void getLast(dataPoint * dp);
	void getlast(uint32_t n, vector<dataPoint> * dpVect);

};

#endif
