# Makefile for Iteration2
#
# Author:
#	Corey Clayton, November 2011
#	Eric Chan, February 2012
#
# Build everything needed for Iteration2
#

SRC = common.c dispatcher.c testRead.c
OBJ = $(SRC:.c=.o)

CC = gcc
DEBUG = -g -DDEBUG
CFLAGS = -Wall -c -fPIC $(DEBUG)
LFLAGS = -Wall -lm $(DEBUG)

all : dispatcher testRead testProducer

dispatcher : dispatcher.o common.o
	$(CC) $(LFLAGS) -o $@ dispatcher.o common.o

testRead : testRead.o common.o
	$(CC) $(LFLAGS) -o $@ testRead.o common.o

testProducer : testProducer.o common.o
	$(CC) $(LFLAGS) -o $@ testProducer.o common.o

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o dispatcher testRead testProducer
