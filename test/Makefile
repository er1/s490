

# Makefile for Blackboard
#
# Author:
#	Corey Clayton, February 2012
#	Eric Chan, February 2012
#
# Build everything needed for Blackboard
#

CSRC = 
CXXSRC = KIdebug.cpp monitorCS.cpp slamKS.cpp slamCS.cpp testCS.cpp testKS.cpp testReadKS.cpp testSock.cpp udpKS.cpp
BINARIES = testSock monitorCS testKS testCS KIdebug udpKS testReadKS slamKS slamCS

include ../Makefile.inc

PROOT = ..

testSock: testSock.o
	$(LD) $(LFLAGS) -o $@ testSock.o

monitorCS: monitorCS.o common
	$(LD) $(LFLAGS) -o $@ monitorCS.o $(PROOT)/common/BlackboardConnection.o $(PROOT)/common/ControlShell.o

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

slamCS: slamCS.o common
	$(LD) $(LFLAGS) -o $@ slamCS.o $(PROOT)/common/BlackboardConnection.o $(PROOT)/common/ControlShell.o

common:
	cd ../common; make
