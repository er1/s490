#include "rpcSrv.h"

vector<knowledgeItem *> * knowledgeItems = new vector<knowledgeItem *>;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
	//initialize some things
	//pthread_t ptSrv;
	pthread_t ptUI;

	//todo: move this?
	
	
	knowledgeItem * e;

	e = new knowledgeItem();
	e->id = KI_A;
	knowledgeItems->push_back(e);
	e = new knowledgeItem();
	e->id = KI_B;
	knowledgeItems->push_back(e);
	e = new knowledgeItem();
	e->id = KI_C;
	knowledgeItems->push_back(e);
	e = new knowledgeItem();
	e->id = KI_D;
	knowledgeItems->push_back(e);

	printf("☢CAUTION!!☢\n");
	
	//start the interface thread
	printf("starting UI thread...");
	pthread_create(&ptUI, NULL, runUI, (void *)NULL);
	printf("\tdone!\n");

	runServer();

	pthread_join(ptUI, NULL);
}


