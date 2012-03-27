# Makefile for Blackboard
#
# Author:
#	Corey Clayton, February 2012
#	Eric Chan, February 2012
#
# Build everything needed for Blackboard
#

CSRC = 
CXXSRC = Blackboard.cpp KnowledgeItem.cpp main.cpp ttyKS.cpp
BINARIES = blackboard ttyKS

include ../Makefile.inc

PROOT = ..

blackboard: main.o Blackboard.o KnowledgeItem.o
	$(LD) $(LFLAGS) -o $@ main.o Blackboard.o KnowledgeItem.o

ttyKS: ttyKS.o common
	$(LD) $(LFLAGS) -o $@ ttyKS.o $(PROOT)/common/BlackboardConnection.o $(PROOT)/common/KnowledgeSource.o

common:
	cd ../common; make