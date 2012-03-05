#include "knowledgeSource.h"

int main()
{
	knowledgeSource * ks = new knowledgeSource(42);

	ks->reg("Test Data 2");

	uint8_t * d =  new uint8_t[4];
	
	d[0] = 'd';
	d[1] = 'e';
	d[2] = 'r';
	d[3] = 'p';
	
	ks->update(4, d);

	return 0;
}
