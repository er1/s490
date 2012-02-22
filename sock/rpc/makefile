all: rpcSrv cli

rpcSrv: rpcSrv.o
	g++ -Wall -lpthread rpcSrv.o srvThread.o uiThread.o event.o -o rpcSrv

rpcSrv.o: srvThread.o uiThread.o event.o
	g++ -Wall -c rpcSrv.cpp

uiThread.o:
	g++ -g -Wall -c uiThread.cpp

srvThread.o:
	g++ -g -Wall -lpthread -c srvThread.cpp

event.o:
	g++ -g -Wall -lpthread -c event.cpp

cli:
	gcc -g -Wall rpcCli.c -o cli

clean:
	rm *o rpcSrv cli

