#include "uiThread.h"

void printAllKI()
{
	for(map<uint32_t, knowledgeItem *>::iterator i=tagMap.begin(); i!=tagMap.end(); ++i)
	{
		(*i).second->print();
	}
}


void * runUI(void * arg)
{
	while(1)
	{
		char in;
		fprintf(stderr, "-->");
		scanf("%c", &in);
		fprintf(stderr, "\n");

		if(in == 'p')
			printAllKI();
		if(in == 'q')
			break;
	}
	return NULL;
}
