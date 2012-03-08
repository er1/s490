#include "uiThread.h"



void doEventA()
{
	fprintf(stderr, "A >>\n");
	(*knowledgeItems)[0]->updateListeners();
}
void doEventB()
{
	fprintf(stderr, "B >>\n");
}
void doEventC()
{
	fprintf(stderr, "C >>\n");
}
void doEventD()
{
	fprintf(stderr, "D >>\n");
}

void * runUI(void * arg)
{
	while(1)
	{
		char in;
		fprintf(stderr, "-->");
		scanf("%c", &in);
		fprintf(stderr, "\n");

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
