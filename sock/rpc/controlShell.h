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

#include <vector>

#include "bbProto.h"
#include "knowledgeSource.h"

#define BUFFSIZE 256

class controlShell
{
private:

	int s;
	uint8_t buf[BUFFSIZE];

public:
	controlShell();
	controlShell(uint32_t t);
	void init();
	void reg(uint32_t t);
	void getLast(dataPoint * dp);
	void getlast(uint32_t n, vector<dataPoint> * dpVect);

};

#endif
