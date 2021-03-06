# Makefile Include for Blackboard
#
# Author:
#	Eric Chan, March 2012
#

SRC = $(CSRC) $(CXXSRC)
OBJ = $(CSRC:.c=.o) $(CXXSRC:.cpp=.o)
ETC = 

PREFIX = 
DEBUG = -g -DDEBUG#-DQUIETDEBUG

CC = $(PREFIX)gcc
CXX = $(PREFIX)g++
LD = $(PREFIX)g++
CFLAGS = -Wall -c -fPIC $(DEBUG) -I.. -fdata-sections -ffunction-sections
CXXFLAGS = $(CFLAGS)
LFLAGS = -Wall $(DEBUG) -I..

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

all: $(OBJ) $(BINARIES) 

clean:
	rm -f $(OBJ) $(BINARIES)

bundle:
	cp $(BINARIES) $(ETC) $(PROOT)/bin || true
