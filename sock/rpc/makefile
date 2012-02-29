CC=g++
CFLAGS = -Wall
bin = bin

all: rpcSrv testCS

rpcSrv: rpcSrv.o
	$(CC) $(CFLAGS) -lpthread $(bin)/rpcSrv.o $(bin)/srvThread.o $(bin)/uiThread.o $(bin)/knowledgeItem.o -o $(bin)/rpcSrv

rpcSrv.o: srvThread.o uiThread.o knowledgeItem.o rpcSrv.cpp
	$(CC) $(CFLAGS) -c rpcSrv.cpp -o $(bin)/rpcSrv.o

uiThread.o: uiThread.cpp
	$(CC) $(CFLAGS) -c uiThread.cpp -o $(bin)/uiThread.o

srvThread.o: srvThread.cpp
	$(CC) $(CFLAGS) -lpthread -c srvThread.cpp -o $(bin)/srvThread.o

knowledgeItem.o: knowledgeItem.cpp
	$(CC) $(CFLAGS) -lpthread -c knowledgeItem.cpp -o $(bin)/knowledgeItem.o

testCS: testCS.c
	gcc $(CFLAGS) testCS.c -o $(bin)/testCS

clean:
	rm $(bin)/*.o $(bin)/rpcSrv $(bin)/testCS

debug: CFLAGS += -g
debug: all