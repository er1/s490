# Makefile for prototype
#
# Author: Corey Clayton, November 2011
#
# Derp
#

all: proto testJob1.so testJob2.so

testJob1.so: testJob1.o
	gcc -g -shared -o testJob1.so testJob1.o

testJob1.o:
	gcc -g -c -fPIC testJob1.c

testJob2.so: testJob2.o
	gcc -g -shared -o testJob2.so testJob2.o

testJob2.o:
	gcc -g -c -fPIC testJob2.c

proto.o:
	gcc -g -rdynamic -ldl -lpthread -c proto.c 

proto: proto.o
	gcc -g -ldl -lpthread proto.o -o proto


clean:
	rm *o