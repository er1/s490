all: rpcSrv cli

rpcSrv: rpcSrv.o
	g++ -Wall -lpthread rpcSrv.o srvThread.o uiThread.o event.o -o rpcSrv

rpcSrv.o: srvThread.o uiThread.o event.o
	g++ -Wall -c rpcSrv.cpp

uiThread.o:
	g++ ${debug} -Wall -c uiThread.cpp

srvThread.o:
	g++ ${debug} -Wall -lpthread -c srvThread.cpp

event.o:
	g++ ${debug} -Wall -lpthread -c event.cpp

cli:
	gcc ${debug} -Wall rpcCli.c -o cli

clean:
	rm *o rpcSrv cli

