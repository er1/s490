# Makefile for Blackboard
#
# Author:
#	Corey Clayton, February 2012
#	Eric Chan, February 2012
#
# Build everything needed for Blackboard
#

CSRC = testRead.c testProducer.c
CXXSRC = main.cpp
BINARIES = dispatcher testRead testProducer

include ../Makefile.inc

PROOT = ..

dispatcher: main.o Job.o
	$(LD) $(LFLAGS) -o $@ main.o 

testProducer: testProducer.o
	$(LD) $(LFLAGS) -o $@ testProducer.o 
	
testRead: testRead.o
	$(LD) $(LFLAGS) -o $@ testRead.o 

# testCS: testCS.o common
# 	$(LD) $(LFLAGS) -o $@ testCS.o $(PROOT)/common/BlackboardConnection.o $(PROOT)/common/ControlShell.o $(PROOT)/common/KnowledgeSource.o

common:
	cd ../common; make
