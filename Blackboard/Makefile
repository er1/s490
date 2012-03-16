# Makefile for Blackboard
#
# Author:
#	Corey Clayton, February 2012
#	Eric Chan, February 2012
#
# Build everything needed for Blackboard
#

CSRC = 
CXXSRC = main.cpp Blackboard.cpp BlackboardConnection.cpp Thread.cpp testSock.cpp monitorKSCS.cpp Packet.cpp
SRC = $(CSRC) $(CXXSRC)
OBJ = $(CSRC:.c=.o) $(CXXSRC:.cpp=.o)
BINARIES = blackboard testSock monitorKSCS

PREFIX = 
DEBUG = -g -DDEBUG

CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
LD = $(PREFIX)g++
CFLAGS = -Wall -c -fPIC $(DEBUG)
CXXFLAGS = $(CFLAGS)
LFLAGS = -Wall -lm -pthread $(DEBUG)

all: $(BINARIES)

# add executable definitions here here...
# <exe>: <.o files>
#	$(LD) $(LFLAGS) -o $@ <.o files>

blackboard: main.o Blackboard.o
	$(LD) $(LFLAGS) -o $@ main.o Blackboard.o
	
testSock: testSock.o
	$(LD) $(LFLAGS) -o $@ testSock.o
	
monitorKSCS: monitorKSCS.o BlackboardConnection.o
	$(LD) $(LFLAGS) -o $@ monitorKSCS.o BlackboardConnection.o

# def'n end here

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) $(BINARIES)

bundle: $(BINARIES)
	tar zvcf deploy.tgz $(BINARIES)
