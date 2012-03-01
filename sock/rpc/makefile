CC=g++
CFLAGS = 
bin = bin

all: blackBoard testCS

blackBoard: blackBoard.o
	$(CC) $(CFLAGS) -lpthread $(bin)/blackBoard.o $(bin)/csSrv.o $(bin)/uiThread.o $(bin)/knowledgeItem.o -o $(bin)/blackBoard

blackBoard.o: csSrv.o uiThread.o knowledgeItem.o blackBoard.cpp
	$(CC) $(CFLAGS) -c blackBoard.cpp -o $(bin)/blackBoard.o

uiThread.o: uiThread.cpp
	$(CC) $(CFLAGS) -c uiThread.cpp -o $(bin)/uiThread.o

csSrv.o: csSrv.cpp
	$(CC) $(CFLAGS) -lpthread -c csSrv.cpp -o $(bin)/csSrv.o

knowledgeItem.o: knowledgeItem.cpp
	$(CC) $(CFLAGS) -lpthread -c knowledgeItem.cpp -o $(bin)/knowledgeItem.o

testCS: testCS.c
	gcc $(CFLAGS) testCS.c -o $(bin)/testCS

clean:
	rm $(bin)/*.o $(bin)/blackBoard $(bin)/testCS

debug: CFLAGS += -g -Wall
debug: all