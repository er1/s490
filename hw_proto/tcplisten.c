#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


int main(int argc, char** argv) {
	const int one = 1;
	struct addrinfo hints;
	struct addrinfo* res;
	int listen_socket;
	int connect_socket;

	if (argc < 3) {
		fprintf(stderr, "usage: tcplisten <port> <command> <arguments> ...\n");
		return -1;
	}

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(NULL, argv[1], &hints, &res) != 0) {
		perror("getaddrinfo");
		exit(-1);
	}

	if ((listen_socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
		perror("socket");
		exit(-1);
	}
	if (setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int)) == -1) {
		perror("setsockopt");
		exit(-1);
	}
	if (bind(listen_socket, res->ai_addr, res->ai_addrlen) != 0) {
		perror("bind");
		exit(-1);
	}
	if (listen(listen_socket, SOMAXCONN) != 0) {
		perror("listen");
		exit(-1);
	}

	for (;;) {
		if ((connect_socket = accept(listen_socket, NULL, NULL)) < 0) {
			perror("accept");
			exit(-1);
		}
		
		if (!fork()) {
			dup2(connect_socket, 0);
			dup2(connect_socket, 1);
			dup2(connect_socket, 2);

			execv(argv[2], argv+2);
			perror("execv");
			//send(connect_socket, "[\"o\"]", 5, 0);
			//close(connect_socket);
			exit(-1);
		}
	}

	return 0;
}
