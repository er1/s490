#include "controlShell.h"

uint32_t tag = 42; //tag for test data

void somethingChanged(dataPoint * d)
{
	printf("got update: [%c]\n", *(d->data));
}

int main()
{
	controlShell * cs =  new controlShell();

	cs->init();
	
	//get the last data point
	dataPoint d;
	cs->getLast(tag, &d);

	printf("last data point -> %c\n", *d.data); //im cheating by knowing its a char ahead of time
	
	//get the last 10 data points
	vector<dataPoint> * v;
	v = cs->getLast(tag, 10);
	printf("getLast returned %p\n", v);

	printf("asked for 10 dataPoints and got --> [");
	for(uint32_t i=0; i<v->size(); ++i)
	{
		printf("%c", *(v->at(i).data));
	}
	printf("]\n");


	//register for test data updates
	cs->reg(tag, somethingChanged);

	while(1)
	{
		//derp...
	}
	
}
