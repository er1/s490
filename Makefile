all:
	cd common; make
	cd Blackboard; make
	cd Dispatcher; make
	cd test; make

clean:
	cd common; make clean
	cd Blackboard; make clean
	cd Dispatcher; make clean
	cd test; make clean
	rm -rf bin

bundle:
	mkdir -p bin
	cd bin; rm -f *
	cd common; make bundle
	cd Blackboard; make bundle
	cd Dispatcher; make bundle
	cd test; make bundle
