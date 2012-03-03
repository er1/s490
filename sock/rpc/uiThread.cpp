#include "uiThread.h"
#include "common.h"

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
		log("-->");
		in = getchar();
		log("\n");

		if(in == 'p')
			printAllKI();
		if(in == 'q')
			break;
	}
	return NULL;
}
