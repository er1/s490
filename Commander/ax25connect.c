/*
   Copyright 2012 Corey Clayton, Eric Chan, Mathieu Dumais-Savard

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netax25/ax25.h>

struct full_sockaddr_ax25 sa_bind;
struct full_sockaddr_ax25 sa_connect;

int main(int argc, char** argv) {
	int sock_ax;
	const char* local_call;
	const char* dest_call;
	const char* message;
	const char* dest_call_list[] = { 0, 0 };
	char buffer[4096];
	const int bufferlen = 4096;
	int len;

	if (argc != 4) {
		fprintf(stderr, "usage: %s <sourcecall> <destcall> <message>\n", (argc>0)?argv[0]:"???");
		exit(-1);
	}

	local_call = argv[1];
	dest_call = argv[2];
	dest_call_list[0] = dest_call;
	message = argv[3];
	len = strlen(message);

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
	ax25_aton_entry(local_call, sa_bind.fsa_digipeater[0].ax25_call);
	ax25_aton_entry(local_call, sa_bind.fsa_ax25.sax25_call.ax25_call);

	sa_connect.fsa_ax25.sax25_family = AF_AX25;
	ax25_aton_arglist(dest_call_list, &sa_connect);

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

	puts("send...");
	write(1, message, len);
	puts("");
	if (send(sock_ax, message, len, 0) <= 0) {
		perror("send");
		exit(-1);
	}
	
	puts("recv...");
	len = recv(sock_ax, buffer, bufferlen, 0);
	if (len <= 0) {
		perror("recv");
		exit(-1);
	}

	write(1, buffer, len);
	puts("");

	return 0;
}
