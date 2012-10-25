#include <stdio.h>
#include <string.h>
#define ZERO(x) memset(&x, 0, sizeof(x))
#define COPY(x, y) memcpy(&x, &y, sizeof(x))
#define CHECK(x, y) if (!(x)) { perror(y); }

#include <errno.h>

#include <termios.h>
#include <fcntl.h>
#include <pty.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if.h>
#include <linux/if_arp.h>
#include <linux/ax25.h>

int main() {
	int master, slave;
	struct termios tm;
	int disc = N_AX25;
	int encap = 4; ///???
	struct ifreq ifr;
	int fd;
	struct sockaddr_ax25 sax25;
	struct sockaddr_in sin;
	char mycall[] = {'V'<<1,'E'<<1,'2'<<1,'E'<<1,'C'<<1,'Q'<<1,'1'<<1};

	unsigned char buffer[256];

	// create a pty pair for the network device
	CHECK(openpty(&master, &slave, NULL, NULL, NULL) == 0, "openpty\n");
	// create a temporary working socket
	CHECK((fd = socket(AF_INET, SOCK_DGRAM, 0)) != -1, "socket\n");

	// prepare line io
	ZERO(tm);
	tm.c_cflag = CS8 | CREAD | CLOCAL;
	CHECK(tcsetattr(master, TCSANOW, &tm) == 0, "tcsetattr\n");
	ZERO(tm);
	tm.c_cflag = CS8 | CREAD | CLOCAL;
	CHECK(tcsetattr(slave, TCSANOW, &tm) == 0, "tcsetattr\n");

	// set ax25
	CHECK((ioctl(master, TIOCSETD, &disc)) != -1, "TIOCSETD\n");
	CHECK((ioctl(master, SIOCSIFENCAP, &encap)) != -1, "SIOCSIFENCAP\n");

	ZERO(ifr);
	CHECK((ioctl(master, SIOCGIFNAME, &ifr)) != -1, "SIOCGIFNAME\n");
	strncpy(ifr.ifr_newname, "ham0", sizeof(ifr.ifr_newname));
	CHECK((ioctl(fd, SIOCSIFNAME, &ifr)) != -1, "SIOCSIFNAME\n");

	ZERO(ifr);
	CHECK((ioctl(master, SIOCGIFNAME, &ifr)) != -1, "SIOCGIFNAME\n");
	ifr.ifr_mtu = 256;
	CHECK(ioctl(fd, SIOCSIFMTU, &ifr) != -1, "SIOCSIFMTU\n");

	// Set callsign
	ZERO(ifr);
	CHECK((ioctl(master, SIOCGIFNAME, &ifr)) != -1, "SIOCGIFNAME\n");
	ZERO(sax25);
	sax25.sax25_family = ARPHRD_AX25;
	sax25.sax25_ndigis = 0;
	COPY(sax25.sax25_call, mycall);
	COPY(ifr.ifr_hwaddr, sax25);
	CHECK(ioctl(fd, SIOCSIFHWADDR, &ifr) != -1, "SIOCSIFHWADDR\n");

	// Enable device
	ZERO(ifr);
	CHECK((ioctl(master, SIOCGIFNAME, &ifr)) != -1, "SIOCGIFNAME\n");
	CHECK((ioctl(fd, SIOCGIFFLAGS, &ifr)) != -1, "SIOCGIFFLAGS\n");
	ifr.ifr_flags &= ~IFF_NOARP;
	ifr.ifr_flags |= IFF_UP | IFF_RUNNING;
	CHECK((ioctl(fd, SIOCSIFFLAGS, &ifr)) != -1, "SIOCSIFFLAGS\n");

	// close temporary fd
	close(fd);

	// go to nonblock
	//fcntl(slave, F_SETFL, fcntl(slave, F_GETFL, 0) | O_NONBLOCK);
	// block for now

	// do io on slave
	while (1) {
		fd_set r, w;
		FD_ZERO(&r);
		FD_ZERO(&w);
		FD_SET(slave, &r);
		//FD_SET(slave, &w);

		select(slave + 1, &r, &w, 0, 0);
		
		int ret;
		ZERO(buffer);
		ret = read(slave, buffer, sizeof(buffer));
		write(1, buffer, sizeof(buffer));
	}
	// wait
	//getchar();
}
