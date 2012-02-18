all: rpcSrv

rpcSrv: rpcSrv.o
	g++ -Wall -lpthread rpcSrv.o srvThread.o uiThread.o -o rpcSrv

rpcSrv.o: srvThread.o uiThread.o
	g++ -Wall -c rpcSrv.cpp

uiThread.o:
	g++ -g -Wall -c uiThread.cpp

srvThread.o:
	g++ -g -Wall -lpthread -c srvThread.cpp

clean:
	rm *o rpcSrv

