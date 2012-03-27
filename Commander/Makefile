CSRC = 
CXXSRC = testUplink.cpp Uplink.cpp 
BINARIES = testUplink 

include ../Makefile.inc

PROOT = ..

#CFLAGS := $(CFLAGS) -DUSE_AX25

LFLAGS := $(LFLAGS) -lax25


testUplink: testUplink.o Uplink.o
	$(LD) $(LFLAGS) -o $@ testUplink.o Uplink.o



#
#listen: ax25listen.c
#	gcc ax25listen.c -o listen -lax25
#connect: ax25connect.c
#	gcc ax25connect.c -o connect -lax25
#testGS:	testGS.cpp
#	g++ testGS.cpp -o testGSx
#clean:
#	rm listen connect testGS
