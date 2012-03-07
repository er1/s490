CC=g++
CFLAGS = 
bin = bin

all: blackBoard testCS testCS2 testKS testKS2

blackBoard: blackBoard.o
	$(CC) $(CFLAGS) -lpthread $(bin)/blackBoard.o $(bin)/csSrv.o $(bin)/ksSrv.o $(bin)/uiThread.o $(bin)/knowledgeItem.o $(bin)/bbThread.o -o $(bin)/blackBoard

blackBoard.o: csSrv.o ksSrv.o uiThread.o knowledgeItem.o bbThread.o blackBoard.cpp
	$(CC) $(CFLAGS) -c blackBoard.cpp -o $(bin)/blackBoard.o

uiThread.o: uiThread.cpp
	$(CC) $(CFLAGS) -c uiThread.cpp -o $(bin)/uiThread.o

csSrv.o: csSrv.cpp
	$(CC) $(CFLAGS) -c csSrv.cpp -o $(bin)/csSrv.o

ksSrv.o: ksSrv.cpp
	$(CC) $(CFLAGS) -c ksSrv.cpp -o $(bin)/ksSrv.o

knowledgeItem.o: knowledgeItem.cpp
	$(CC) $(CFLAGS) -lpthread -c knowledgeItem.cpp -o $(bin)/knowledgeItem.o

bbThread.o: bbThread.cpp
	$(CC) $(CFLAGS) -lpthread -c bbThread.cpp -o $(bin)/bbThread.o

knowledgeSource.o: knowledgeSource.cpp
	$(CC) $(CFLAGS) -c knowledgeSource.cpp -o $(bin)/knowledgeSource.o

controlShell.o: controlShell.cpp
	$(CC) $(CFLAGS) -c controlShell.cpp -o $(bin)/controlShell.o

testCS: testCS.c
	gcc $(CFLAGS) testCS.c -o $(bin)/testCS

testCS2: testCS2.o
	$(CC) $(CFLAGS) -lpthread $(bin)/testCS2.o $(bin)/controlShell.o -o $(bin)/testCS2

testCS2.o: testCS2.cpp controlShell.o
	$(CC) $(CFLAGS) -c testCS2.cpp -o $(bin)/testCS2.o

testKS: testKS.c
	gcc $(CFLAGS) testKS.c -o $(bin)/testKS

testKS2.o: testKS2.cpp knowledgeSource.o
	$(CC) $(CFLAGS) -c testKS2.cpp -o $(bin)/testKS2.o

testKS2: testKS2.o
	$(CC) $(CFLAGS) $(bin)/testKS2.o $(bin)/knowledgeSource.o -o $(bin)/testKS2

clean:
	rm $(bin)/*.o $(bin)/blackBoard $(bin)/testCS $(bin)/testKS $(bin)/testKS2

debug: CFLAGS += -g -Wall
debug: all