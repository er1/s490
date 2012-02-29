CC=g++
CFLAGS = -Wall
bin = bin

all: rpcSrv cli

rpcSrv: rpcSrv.o
	$(CC) $(CFLAGS) -lpthread $(bin)/rpcSrv.o $(bin)/srvThread.o $(bin)/uiThread.o $(bin)/event.o -o $(bin)/rpcSrv

rpcSrv.o: srvThread.o uiThread.o event.o rpcSrv.cpp
	$(CC) $(CFLAGS) -c rpcSrv.cpp -o $(bin)/rpcSrv.o

uiThread.o: uiThread.cpp
	$(CC) $(CFLAGS) -c uiThread.cpp -o $(bin)/uiThread.o

srvThread.o: srvThread.cpp
	$(CC) $(CFLAGS) -lpthread -c srvThread.cpp -o $(bin)/srvThread.o

event.o: event.cpp
	$(CC) $(CFLAGS) -lpthread -c event.cpp -o $(bin)/event.o

cli: rpcCli.c
	gcc $(CFLAGS) rpcCli.c -o $(bin)/cli

clean:
	rm $(bin)/*.o $(bin)/rpcSrv $(bin)/cli

debug: CFLAGS += -g
debug: all