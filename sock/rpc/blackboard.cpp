#include "blackboard.h"

#include <cstdio>
#include <cstring>
#include <deque>
#include <map>

#include <pthread.h>
#include <signal.h>

#include "common.h"
#include "tags.h"
#include "csSrv.h"
#include "ksSrv.h"
#include "uiThread.h"

using namespace std;

deque<knowledgeItem *> * knowledgeItems;
map<bbtag, knowledgeItem *> tagMap;
bbThread * threadManager;

void pipeBurst(int) {
	log("PIPE BURST!!!\n");
}

int main()
{
	// if a socket fails, we will get SIGPIPE. handle it
	signal(SIGPIPE, pipeBurst);

	threadManager = new bbThread();
	knowledgeItems = new deque<knowledgeItem *>;
	knowledgeItems->clear();

	//initialize some things
	pthread_t ptUI;

	log("CAUTION!!\n");
	
	//start the interface thread as a normal pthread
	log("starting UI thread\n");
	pthread_create(&ptUI, NULL, runUI, (void *)NULL);
	
	//start managed threads
	threadManager->createDetached(runCSServer);
	threadManager->createDetached(runKSServer);
	//pthread_create(&ptCS, NULL, runCSServer, (void *)NULL);
	//pthread_create(&ptKS, NULL, runKSServer, (void *)NULL);
	
	// whatif no UI thread?
	pthread_join(ptUI, NULL);
	log("Quitting....\n");
	
	return 0;
}
