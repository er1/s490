#ifndef _KS_H_
#define _KS_H_

#include <stdint.h>
#define BUFFSIZE (256)

class knowledgeSource
{
private:
	bool initialized;
	uint32_t tag;

	int s;
	uint8_t buf[BUFFSIZE];

public:
	knowledgeSource();
	knowledgeSource(uint32_t t);
	~knowledgeSource();
	void init();
	void setTag(uint32_t t);
	void reg(const char * name);
	void update(uint32_t len, uint8_t * data);
};

#endif 
