# Makefile for prototype
#
# Author: Corey Clayton, November 2011
#
# Derp
#

all: proto testJob1.so testJob2.so

testJob1.so: testJob1.o
	gcc -shared -o testJob1.so testJob1.o

testJob1.o:
	gcc -c -fPIC testJob1.c

testJob2.so: testJob2.o
	gcc -shared -o testJob2.so testJob2.o

testJob2.o:
	gcc -c -fPIC testJob2.c

proto.o:
	gcc -rdynamic -ldl -lpthread -c proto.c 

proto: proto.o
	gcc -ldl -lpthread proto.o -o proto


clean:
	rm *o