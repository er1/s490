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
BINARIES = blackboard testSock monitorKSCS testKS testCS KIdebug

include ../Makefile.inc

PROOT = ..

blackboard: main.o Blackboard.o KnowledgeItem.o
	$(LD) $(LFLAGS) -o $@ main.o Blackboard.o KnowledgeItem.o

testSock: testSock.o
	$(LD) $(LFLAGS) -o $@ testSock.o

monitorKSCS: monitorKSCS.o common
	$(LD) $(LFLAGS) -o $@ monitorKSCS.o $(PROOT)/common/BlackboardConnection.o

testCS: testCS.o common
	$(LD) $(LFLAGS) -o $@ testCS.o $(PROOT)/common/BlackboardConnection.o $(PROOT)/common/ControlShell.o $(PROOT)/common/KnowledgeSource.o

testKS: testKS.o common
	$(LD) $(LFLAGS) -o $@ testKS.o $(PROOT)/common/BlackboardConnection.o $(PROOT)/common/KnowledgeSource.o

KIdebug: KIdebug.o
	$(LD) $(LFLAGS) -o $@ KIdebug.o

common:
	cd ../common; make
