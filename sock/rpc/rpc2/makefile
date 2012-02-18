all: rpcSrv

rpcSrv: rpcSrv.o
	g++ -Wall -lpthread rpcSrv.o srvThread.o -o rpcSrv

rpcSrv.o: srvThread.o
	g++ -Wall -c rpcSrv.cpp

#client.o:
#	g++ -g -Wall -c client.c

srvThread.o:
	g++ -g -Wall -lpthread -c srvThread.cpp

clean:
	rm *o demoSrv

