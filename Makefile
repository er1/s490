all:
	cd common; make
	cd Blackboard; make
	cd Dispatcher; make

clean:
	cd common; make clean
	cd Blackboard; make clean
	cd Dispatcher; make clean
