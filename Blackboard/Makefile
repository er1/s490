# Makefile for Blackboard
#
# Author:
#	Corey Clayton, February 2012
#	Eric Chan, February 2012
#
# Build everything needed for Blackboard
#

CSRC = 
CXXSRC = Blackboard.cpp KIdebug.cpp main.cpp monitorKSCS.cpp testKS.cpp testCS.cpp testSock.cpp KnowledgeItem.cpp
BINARIES = blackboard testSock monitorKSCS testKS testCS KIdebug udpKS testReadKS ttyKS slamKS

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
	
testReadKS: testReadKS.o common
	$(LD) $(LFLAGS) -o $@ testReadKS.o $(PROOT)/common/BlackboardConnection.o $(PROOT)/common/KnowledgeSource.o
	
udpKS: udpKS.o common
	$(LD) $(LFLAGS) -o $@ udpKS.o $(PROOT)/common/BlackboardConnection.o $(PROOT)/common/KnowledgeSource.o
	
ttyKS: ttyKS.o common
	$(LD) $(LFLAGS) -o $@ ttyKS.o $(PROOT)/common/BlackboardConnection.o $(PROOT)/common/KnowledgeSource.o

slamKS: slamKS.o common
	$(LD) $(LFLAGS) -o $@ slamKS.o $(PROOT)/common/BlackboardConnection.o $(PROOT)/common/KnowledgeSource.o

common:
	cd ../common; make
