#include "uiThread.h"



void doEventA()
{
	printf("A >>\n");
	(*events)[0]->updateListeners();
}
void doEventB()
{
	printf("B >>\n");
}
void doEventC()
{
	printf("C >>\n");
}
void doEventD()
{
	printf("D >>\n");
}

void * runUI(void * arg)
{
	while(1)
	{
		char in;
		printf("-->");
		scanf("%c", &in);
		printf("\n");

		if(in == 'a')
			doEventA();
		if(in == 'b')
			doEventB();
		if(in == 'c')
			doEventC();
		if(in == 'd')
			doEventD();
	}
	return NULL;
}
