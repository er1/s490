#include "Uplink.h"

int main()
{
	printf("TODO: everything");

	Uplink up;
	up.prepareLink();

	Packet p;
    p.resize(4);
    p[0] = 'o';
    p[1] = 'H';
    p[2] = 'a';
    p[3] = 'i';

	up.send(p);
	up.processOutgoing();

	return 0;
}
