#include "rpcSrv.h"

vector<event *> * events = new vector<event *>;

int main()
{
	//initialize some things
	//pthread_t ptSrv;
	pthread_t ptUI;

	//todo: move this?
	
	
	event * e;

	e = new event();
	e->id = EVENT_A;
	events->push_back(e);
	e = new event();
	e->id = EVENT_B;
	events->push_back(e);
	e = new event();
	e->id = EVENT_C;
	events->push_back(e);
	e = new event();
	e->id = EVENT_D;
	events->push_back(e);

	
	//start the server thread
/*	printf("starting server thread...");
	pthread_create(&ptSrv, NULL, runServer, (void *)NULL);
	printf("\tdone!\n");
*/

	//start the interface thread
	printf("starting client thread...");
	pthread_create(&ptUI, NULL, runUI, (void *)NULL);
	printf("\tdone!\n");

	runServer();

	//pthread_join(ptSrv, NULL);
	pthread_join(ptUI, NULL);
}


