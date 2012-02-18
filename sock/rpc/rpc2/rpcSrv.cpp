#include "rpcSrv.h"

int main()
{
	//initialize some things
	pthread_t ptSrv, ptUserx;
	
	//start the server thread
	printf("starting server thread...");
	pthread_create(&ptSrv, NULL, runServer, (void *)NULL);
	printf("done");
	//start the interface thread
	printf("starting client thread...");
	printf("done");
}


