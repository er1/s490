# Makefile for Blackboard
#
# Author:
#	Corey Clayton, February 2012
#	Eric Chan, February 2012
#
# Build everything needed for Blackboard
#

CSRC = 
CXXSRC = Blackboard.cpp KnowledgeItem.cpp main.cpp ttyKS.cpp timeKS.cpp timePR.cpp
BINARIES = blackboard ttyKS timeKS timePR

include ../Makefile.inc

PROOT = ..

blackboard: main.o Blackboard.o KnowledgeItem.o
	$(LD) $(LFLAGS) -o $@ main.o Blackboard.o KnowledgeItem.o

ttyKS: ttyKS.o common
	$(LD) $(LFLAGS) -o $@ ttyKS.o $(PROOT)/common/BlackboardConnection.o $(PROOT)/common/KnowledgeSource.o

timeKS: timeKS.o common
	$(LD) $(LFLAGS) -o $@ timeKS.o $(PROOT)/common/BlackboardConnection.o $(PROOT)/common/KnowledgeSource.o
	
timePR: timePR.o common
	$(LD) $(LFLAGS) -o $@ timePR.o $(PROOT)/common/BlackboardConnection.o $(PROOT)/common/KnowledgeSource.o $(PROOT)/common/ControlShell.o 

common:
	cd ../common; make