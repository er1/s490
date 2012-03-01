#include "blackBoard.h"

vector<knowledgeItem *> * knowledgeItems = new vector<knowledgeItem *>;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

map<uint32_t, knowledgeItem *> tagMap;

int main()
{
	//initialize some things
	pthread_t ptUI, ptCS, ptKS;

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
	pthread_create(&ptCS, NULL, runCSServer, (void *)NULL);
	pthread_create(&ptKS, NULL, runKSServer, (void *)NULL);
	printf("\tdone!\n");

	

	runServer();

	pthread_join(ptUI, NULL);
}


