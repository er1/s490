all: sim

sim: sim.o comms.o power.o aocs.o rtc.o
	gcc -g -Wall sim.o comms.o power.o aocs.o rtc.o -o sim

sim.o: sim.c sim.h
	gcc -g -Wall -c sim.c

comms.o: comms.c comms.h
	gcc -g -Wall -c comms.c

power.o: power.c power.h
	gcc -g -Wall -c power.c

aocs.o: aocs.c aocs.h
	gcc -g -Wall -c aocs.c

rtc.o: rtc.c rtc.h
	gcc -g -Wall -c rtc.c

clean:
	rm -rf *o sim

