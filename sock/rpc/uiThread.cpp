#include "uiThread.h"
#include "common.h"


void doEventA()
{
	log("A >>\n");
	(*knowledgeItems)[0]->updateListeners();
}
void doEventB()
{
	log("B >>\n");
}
void doEventC()
{
	log("C >>\n");
}
void doEventD()
{
	log("D >>\n");
}

void * runUI(void * arg)
{
	while(1)
	{
		char in;
		log("-->");
		scanf("%c", &in);
		log("\n");

		if(in == 'a')
			doEventA();
		if(in == 'b')
			doEventB();
		if(in == 'c')
			doEventC();
		if(in == 'd')
			doEventD();
		if(in == 'q')
			break;
	}
	return NULL;
}
