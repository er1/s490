#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netax25/ax25.h>

struct full_sockaddr_ax25 sa_bind;
struct full_sockaddr_ax25 sa_connect;

int main(int argc, char** argv) {
	int sock_ax;
	const char* ve2ecq = "VE2ECQ-1";
	const char* va2hax = "VA2HAX-1";
	const char* ve2ecqlist[] = { ve2ecq, 0 };
	const char* va2haxlist[] = { va2hax, 0 }; 

	puts("socket...");

	// create socket
	if ((sock_ax = socket(PF_AX25, SOCK_SEQPACKET, 0)) == -1) {
		perror("socket");
		exit(-1);
	}

	puts("sockaddr...");

	// define address
	sa_bind.fsa_ax25.sax25_family = AF_AX25;
	sa_bind.fsa_ax25.sax25_ndigis = 1;
	ax25_aton_entry(ve2ecq, sa_bind.fsa_digipeater[0].ax25_call);
	ax25_aton_entry(ve2ecq, sa_bind.fsa_ax25.sax25_call.ax25_call);

	sa_connect.fsa_ax25.sax25_family = AF_AX25;
	ax25_aton_arglist(ve2ecqlist, &sa_connect);

	puts("bind...");

	// bind socket to address
	if (bind(sock_ax, (struct sockaddr*)&sa_bind, sizeof(struct full_sockaddr_ax25)) == -1) {
		perror("bind");
		exit(-1);
	}

	puts("connect...");

	// attempt to connect to address
	if (connect(sock_ax, (struct sockaddr*)&sa_connect, sizeof(struct full_sockaddr_ax25)) != 0) {
		perror("connect");
		exit(-1);
	}

	return 0;
}
