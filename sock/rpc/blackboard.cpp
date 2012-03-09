#include "blackboard.h"

#include <cstdio>
#include <cstring>
#include <deque>
#include <map>

#include <pthread.h>
#include <signal.h>

#include "csSrv.h"
#include "ksSrv.h"
#include "uiThread.h"

using namespace std;

map<uint32_t, knowledgeItem *> tagMap;

bbThread * threadManager;

void pipeBurst(int) 
{
	fprintf(stderr, "PIPE BURST!!!\n");
}

int main()
{
	
	signal(SIGPIPE, pipeBurst);

	threadManager = new bbThread();

	//initialize some things
	pthread_t ptUI;

	//start the interface thread as a normal pthread
	fprintf(stderr, "starting UI thread\n");
	pthread_create(&ptUI, NULL, runUI, (void *)NULL);
	
	//start managed threads
	threadManager->createDetached(runCSServer);
	threadManager->createDetached(runKSServer);
	//pthread_create(&ptCS, NULL, runCSServer, (void *)NULL);
	//pthread_create(&ptKS, NULL, runKSServer, (void *)NULL);
	

	
	pthread_join(ptUI, NULL);
	fprintf(stderr, "Quitting....\n");
	
	return 0;

}




