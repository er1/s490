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

//Corey's fancy function for visualizing binary data
void hexDump(void * data, size_t byteLen)
{
	unsigned int line, col;
	char hex[49];
	char ascii[17];
	
	memset(hex, 0, 48);
	memset(ascii, 0, 16);
	
	if(byteLen == 0) 
		return;
	
	fprintf(stderr, "0x  00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f \n");
	for(line=0; line<(byteLen/16)+1; line++)
	{
		for(col=0; col<16; col++)
		{
			unsigned int pos = 16*line + col;
			unsigned char curByte;
			
			if(pos>=byteLen)
				break;
			
			curByte = *(((unsigned char *)(data)+pos));
			sprintf(hex, "%s%02x ", hex, curByte);
			
			if( curByte>=32 && curByte<127 )
				sprintf(ascii, "%s%c", ascii, curByte);
			else
				sprintf(ascii, "%s%s", ascii, ".");
		}
		fprintf(stderr, "%02x  %-48s %-16s\n", line, hex, ascii);
		memset(hex, 0, 48);
		memset(ascii, 0, 16);
	}
}


