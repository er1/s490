# Makefile for Blackboard
#
# Author:
#	Corey Clayton, February 2012
#	Eric Chan, February 2012
#
# Build everything needed for Blackboard
#

CSRC = testRead.c testProducer.c
CXXSRC = main.cpp Job.cpp JobManager.cpp RunCondition.cpp
BINARIES = dispatcher testRead testProducer
ETC = jobs.txt

include ../Makefile.inc

PROOT = ..

dispatcher: main.o JobManager.o Job.o RunCondition.o common
	$(LD) $(LFLAGS) -o $@ main.o JobManager.o Job.o RunCondition.o $(PROOT)/common/BlackboardConnection.o $(PROOT)/common/ControlShell.o  $(PROOT)/common/KnowledgeSource.o

testProducer: testProducer.o
	$(LD) $(LFLAGS) -o $@ testProducer.o 
	
testRead: testRead.o
	$(LD) $(LFLAGS) -o $@ testRead.o 

common:
	cd ../common; make
