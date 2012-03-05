#include "blackBoard.h"
//FIXME -- move globals to header?
vector<knowledgeItem *> * knowledgeItems = new vector<knowledgeItem *>;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

map<uint32_t, knowledgeItem *> tagMap;

bbThread * threadManager;

int main()
{
	threadManager = new bbThread();

	//initialize some things
	pthread_t ptUI;

	//todo: move this?
	
	
	knowledgeItem * e;

	e = new knowledgeItem();
	e->id = KI_A;
	knowledgeItems->push_back(e);
	e = new knowledgeItem();
	e->id = KI_B;
	knowledgeItems->push_back(e);
	e = new knowledgeItem();
	e->id = KI_C;
	knowledgeItems->push_back(e);
	e = new knowledgeItem();
	e->id = KI_D;
	knowledgeItems->push_back(e);
	
	printf("☢CAUTION!!☢\n");
	
	//start the interface thread as a normal pthread
	printf("starting UI thread\n");
	pthread_create(&ptUI, NULL, runUI, (void *)NULL);
	
	//start managed threads
	threadManager->createDetached(runCSServer);
	threadManager->createDetached(runKSServer);
	//pthread_create(&ptCS, NULL, runCSServer, (void *)NULL);
	//pthread_create(&ptKS, NULL, runKSServer, (void *)NULL);
	

	
	pthread_join(ptUI, NULL);
	printf("Quitting....\n");
	
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
	
	printf("0x  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F \n");
	for(line=0; line<(byteLen/16)+1; line++)
    {
		for(col=0; col<16; col++)
		{
			unsigned int pos = 16*line + col;
			unsigned char curByte;
			
			if(pos>=byteLen)
				break;
			
			curByte = *(((unsigned char *)(data)+pos));
			sprintf(hex, "%s%02X ", hex, curByte);
			
			if( curByte>=32 && curByte<127 )
				sprintf(ascii, "%s%c", ascii, curByte);
			else
				sprintf(ascii, "%s%s", ascii, ".");
		}
		printf("%02X  %-48s %-16s\n", line, hex, ascii);
		memset(hex, 0, 48);
		memset(ascii, 0, 16);
    }
}


