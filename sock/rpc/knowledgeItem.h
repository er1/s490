#ifndef _KI_H_
#define _KI_H_

#include <deque>
#include <cstdio>
#include <pthread.h>
#include <string>
#include <list>
#include <map>
#include "blackboard.h"

using namespace std;

class remote_callback
{
public:
	int socket;
	uint32_t addr;
};

class dataPoint
{
public:
	uint32_t size;
	uint8_t * data;

	dataPoint();
	~dataPoint();
};

class knowledgeItem
{
private:
	string name;
	uint32_t storageSize;
	deque<remote_callback *> listeners;
	list<dataPoint *> dataList;

	pthread_mutex_t mutex;

public:
	int id;
	
	//int data;

	knowledgeItem();
	void setName(char * str);
	void update(uint32_t len, uint8_t * newData);
	void setStorageSize(uint32_t size);
	void addListenerOnSock(uint32_t cbA, int sock);
	void updateListeners();
	void removeListenersOnSock(int sock);
	
	void sendLastNdataPoints(int sock, uint32_t n);//there is probably a better way to do this
};


//extern pthread_mutex_t mutex; //FIXME

extern deque<knowledgeItem *> * knowledgeItems;

extern map<uint32_t, knowledgeItem *> tagMap;

#endif