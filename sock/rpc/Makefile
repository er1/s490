# Makefile for Iteration2
#
# Author:
#	Corey Clayton, February 2012
#	Eric Chan, February 2012
#
# Build everything needed for Blackboard
#

CSRC = testCS.c testKS.c
CXXSRC = bbThread.cpp blackBoard.cpp controlShell.cpp csSrv.cpp knowledgeItem.cpp knowledgeSource.cpp ksSrv.cpp testCS2.cpp testKS2.cpp uiThread.cpp
SRC = $(CSRC) $(CXXSRC)
OBJ = $(CSRC:.c=.o) $(CXXSRC:.cpp=.o)
BINARIES = blackBoard testCS testCS2 testKS testKS2

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

blackBoard: blackBoard.o csSrv.o ksSrv.o uiThread.o knowledgeItem.o bbThread.o
	$(LD) $(LFLAGS) -o $@ blackBoard.o csSrv.o ksSrv.o uiThread.o knowledgeItem.o bbThread.o

testCS: testCS.o
	$(LD) $(LFLAGS) -o $@ testCS.o

testCS2: testCS2.o controlShell.o knowledgeItem.o
	$(LD) $(LFLAGS) -o $@ testCS2.o controlShell.o knowledgeItem.o

testKS: testKS.o
	$(LD) $(LFLAGS) -o $@ testKS.o

testKS2: testKS2.o knowledgeSource.o
	$(LD) $(LFLAGS) -o $@ testKS2.o knowledgeSource.o

# def'n end here

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) $(BINARIES)
