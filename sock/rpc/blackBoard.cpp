#include "blackBoard.h"
//FIXME -- move globals to header?
vector<knowledgeItem *> * knowledgeItems = new vector<knowledgeItem *>;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

map<uint32_t, knowledgeItem *> tagMap;

bbThread * threadManager;

int main()
{
	threadManager = new bbThread();

	//initialize some things
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
	
	//start the interface thread as a normal pthread
	printf("starting UI thread\n");
	pthread_create(&ptUI, NULL, runUI, (void *)NULL);
	
	//start managed threads
	threadManager->createDetached(runCSServer);
	threadManager->createDetached(runKSServer);
	//pthread_create(&ptCS, NULL, runCSServer, (void *)NULL);
	//pthread_create(&ptKS, NULL, runKSServer, (void *)NULL);
	

	
	pthread_join(ptUI, NULL);
	printf("Quitting....\n");
	
	return 0;

}


