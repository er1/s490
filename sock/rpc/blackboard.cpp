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
	
	log("0x  00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f \n");
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
		log("%02x  %-48s %-16s\n", line, hex, ascii);
		memset(hex, 0, 48);
		memset(ascii, 0, 16);
	}
}


