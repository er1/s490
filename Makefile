all:
	cd common; make
	cd Blackboard; make
	cd Dispatcher; make

clean:
	cd common; make clean
	cd Blackboard; make clean
	cd Dispatcher; make clean

bundle:
	mkdir -p bin
	cd bin; rm -f *
	cd common; make bundle
	cd Blackboard; make bundle
	cd Dispatcher; make bundle

