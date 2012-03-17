all: listen connect

listen: ax25listen.c
	gcc ax25listen.c -o listen -lax25
connect: ax25connect.c
	gcc ax25connect.c -o connect -lax25

clean:
	rm listen connect
