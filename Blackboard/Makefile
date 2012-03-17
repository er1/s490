# Makefile for Blackboard
#
# Author:
#	Corey Clayton, February 2012
#	Eric Chan, February 2012
#
# Build everything needed for Blackboard
#

CSRC = 
CXXSRC = Blackboard.cpp BlackboardConnection.cpp ControlShell.cpp KIdebug.cpp KnowledgeSource.cpp Packet.cpp Thread.cpp main.cpp monitorKSCS.cpp testKS.cpp testCS.cpp testSock.cpp KnowledgeItem.cpp
SRC = $(CSRC) $(CXXSRC)
OBJ = $(CSRC:.c=.o) $(CXXSRC:.cpp=.o)
BINARIES = blackboard testSock monitorKSCS testKS testCS KIdebug

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

blackboard: main.o Blackboard.o KnowledgeItem.o
	$(LD) $(LFLAGS) -o $@ main.o Blackboard.o KnowledgeItem.o
	
testSock: testSock.o
	$(LD) $(LFLAGS) -o $@ testSock.o
	
monitorKSCS: monitorKSCS.o BlackboardConnection.o
	$(LD) $(LFLAGS) -o $@ monitorKSCS.o BlackboardConnection.o

testCS: testCS.o BlackboardConnection.o ControlShell.o
	$(LD) $(LFLAGS) -o $@ testCS.o BlackboardConnection.o ControlShell.o
	
testKS: testKS.o BlackboardConnection.o KnowledgeSource.o
	$(LD) $(LFLAGS) -o $@ testKS.o BlackboardConnection.o KnowledgeSource.o

KIdebug: KIdebug.o
	$(LD) $(LFLAGS) -o $@ KIdebug.o

# def'n end here

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) $(BINARIES)

bundle: $(BINARIES)
	tar zvcf deploy.tgz $(BINARIES)
