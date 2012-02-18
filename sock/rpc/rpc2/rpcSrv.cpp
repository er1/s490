#include "rpcSrv.h"

int main()
{
	//initialize some things
	pthread_t ptSrv;
	//pthread_t ptUserx;
	
	//start the server thread
	printf("starting server thread...");
	pthread_create(&ptSrv, NULL, runServer, (void *)NULL);
	printf("\tdone!\n");
	//start the interface thread
	printf("starting client thread...");
	printf("\tdone!\n");

	pthread_join(ptSrv, NULL);
}


