#include "knowledgeItem.h"
#include <sys/socket.h>
#include <cstring>

dataPoint::dataPoint()
{
	size = 0;
	data = NULL;
}

dataPoint::~dataPoint()
{
	printf("destroy datapoint: size=%d data at addr=%p\n", size, data);
	if(data!=NULL)
		delete[] data;
}

knowledgeItem::knowledgeItem()
{
	pthread_mutex_init(&mutex, NULL);

	pthread_mutex_lock(&mutex);
	//by default we keep one data point
	storageSize = 1;
	pthread_mutex_unlock(&mutex);
}

void knowledgeItem::setName(char * str)
{
	pthread_mutex_lock(&mutex);
	name = str;
	pthread_mutex_unlock(&mutex);
}

void knowledgeItem::update(uint32_t len, uint8_t * newData)
{
	dataPoint * d = new dataPoint();
	d->size = len;
	d->data = newData;
	pthread_mutex_lock(&mutex);
	if(dataList.size() == storageSize)
	{
		dataList.pop_front();
	}
	dataList.push_back(d);
	pthread_mutex_unlock(&mutex);
	updateListeners();
	printf("Update KI [%s] with %d bytes\n", name.c_str(), len);
	printf("[%s] has %d/%d dataPoints", name.c_str(), dataList.size(), storageSize);
}

void knowledgeItem::setStorageSize(uint32_t size)
{
	printf("[%s]changing storage size from %d to %d", name.c_str(), storageSize, size);
	pthread_mutex_lock(&mutex);
	//if the new size is smaller than current size
	//need to shrink the list
	while(size < dataList.size())
	{
		delete dataList.front();
		dataList.pop_front();
	}
	storageSize = size;
	pthread_mutex_unlock(&mutex);
	printf("[%s] has %d/%d dataPoints", name.c_str(), dataList.size(), storageSize);
}

void knowledgeItem::addListenerOnSock(uint32_t cbA, int sock)
{
	remote_callback * rcb = new remote_callback;
	rcb->socket = sock;
	rcb->addr = cbA;

	pthread_mutex_lock(&mutex);
	listeners.push_back(rcb);
	pthread_mutex_unlock(&mutex);
}

void knowledgeItem::updateListeners()
{
	uint8_t buf[16];
	remote_callback * rc;
	dataPoint * d;

	printf("update listeners...\n");
	pthread_mutex_lock(&mutex);
	d = dataList.back();
	for(unsigned int i = 0; i < listeners.size(); ++i)
	{
		rc = listeners[i];
		printf("callback: <knowledgeItem %d> %#X, %#X\n", id, rc->socket, rc->addr);
		buf[0] = OP_SEND_CALLBACK; 
		memcpy(buf+1, &(rc->addr), 4);//TODO: endian
		memcpy(buf+5, &(d->size), 4);//not sure why i used memcpy here...
		send(rc->socket, buf, 9, 0);
		send(rc->socket, d->data, d->size, 0);
	}
	pthread_mutex_unlock(&mutex);
}

void knowledgeItem::removeListenersOnSock(int sock)
{
	pthread_mutex_lock(&mutex);
	for(vector<remote_callback *>::iterator i=listeners.begin(); i<listeners.end(); ++i)
	{
		if((*i)->socket == sock)
		{
			printf("Removing listener on socket %#X from knowledgeItem %d\n", sock, id);
			remote_callback * rcb = *i;
			delete rcb;
			listeners.erase(i);
		}
	}
	pthread_mutex_unlock(&mutex);
}

//this is pretty much custom made for the OP_RET_LAST messgage
void knowledgeItem::sendLastNdataPoints(int sock, uint32_t n)
{
	printf("sendLastNdataPoints N=%d\n", n);
	pthread_mutex_lock(&mutex);
	if(dataList.size() < n)
	{
		uint8_t num[4];
		*(uint32_t *)num = dataList.size();
		//send all the points we have
		send(sock, num, 4, 0);
	
		
		list<dataPoint *>::reverse_iterator rit;
		for(rit=dataList.rbegin(); rit!=dataList.rend(); ++rit)
		{
			dataPoint * tmp = *rit;
			*(uint8_t *)num = tmp->size;
			send(sock, num, 4, 0);
			send(sock, tmp->data, tmp->size, 0);
		}
		pthread_mutex_unlock(&mutex);
		return;
	}

	//otherwize we need only send n
	uint8_t num[4];
	*(uint32_t *)num = n;
	send(sock, num, 4, 0);
	
	uint32_t count = 0;
	list<dataPoint *>::reverse_iterator rit;
	for(rit=dataList.rbegin(); rit!=dataList.rend() && count < n; ++rit)
	{
		dataPoint * tmp = *rit;
		*(uint8_t *)num = tmp->size;
		send(sock, num, 4, 0);
		send(sock, tmp->data, tmp->size, 0);
		++count;
	}
	
	pthread_mutex_unlock(&mutex);
}
