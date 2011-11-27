# Makefile for prototype
#
# Author: Corey Clayton, November 2011
#
# Derp
#

all: proto testRead.so testProc.so testWrite.so

testRead.so: testRead.o
	gcc -g -shared -o testRead.so testRead.o

testRead.o: testRead.c testRead.h
	gcc -g -c -fPIC testRead.c

testProc.so: testProc.o
	gcc -g -shared -o testProc.so testProc.o

testProc.o: testProc.c testProc.h
	gcc -g -c -fPIC testProc.c

testWrite.so: testWrite.o
	gcc -g -shared -o testWrite.so testWrite.o

testWrite.o: testWrite.c testWrite.h
	gcc -g -c -fPIC testWrite.c


testJob1.so: testJob1.o
	gcc -g -shared -o testJob1.so testJob1.o

testJob1.o:
	gcc -g -c -fPIC testJob1.c

testJob2.so: testJob2.o
	gcc -g -shared -o testJob2.so testJob2.o

testJob2.o:
	gcc -g -c -fPIC testJob2.c

proto.o: proto.c
	gcc -g -rdynamic -c proto.c 

proto: proto.o
	gcc -g -ldl -lpthread proto.o -o proto


clean:
	rm *.o *.so proto
