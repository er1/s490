#include <cstdio>
#include "GroundConnector.h"
#include "Listener.h"

int main()
{
	GroundConnector gc;

	gc.connectSat();

	gc.disconnectSat();

	printf("derp\n");
	return 0;
}
