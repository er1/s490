# Makefile for Blackboard
#
# Author:
#	Corey Clayton, February 2012
#	Eric Chan, March 2012
#
# Build everything needed
#

CSRC = 
CXXSRC = BlackboardConnection.cpp ControlShell.cpp DataPoint.cpp KnowledgeSource.cpp Packet.cpp Thread.cpp
SRC = $(CSRC) $(CXXSRC)
OBJ = $(CSRC:.c=.o) $(CXXSRC:.cpp=.o)
BINARIES = 

PREFIX = 
DEBUG = -g -DDEBUG

CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
LD = $(PREFIX)g++
CFLAGS = -Wall -c -fPIC $(DEBUG) -I..
CXXFLAGS = $(CFLAGS)
LFLAGS = -Wall $(DEBUG) -I..

all: $(BINARIES) $(OBJ)

# add executable definitions here here...
# <exe>: <.o files>
#	$(LD) $(LFLAGS) -o $@ <.o files>

# def'n end here

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(OBJ) $(BINARIES)

bundle: $(BINARIES)
	tar zvcf deploy.tgz $(BINARIES)
