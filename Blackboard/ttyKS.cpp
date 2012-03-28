#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include <vector>
#include <errno.h>

#include <common/common.h>
#include <common/KnowledgeSource.h>

int main(int argc, char** argv) {
    termios tio;
    int tty_fd;
    timeval tv;
    //fd_set fdr;

    tcgetattr(tty_fd, &tio);

    memset(&tio, 0, sizeof (tio));
    tio.c_iflag = 0;
    tio.c_oflag = 0;
    tio.c_cflag = CS8 | CREAD | CLOCAL | HUPCL; // 8n1, see termios.h for more information
    tio.c_lflag = 0;
    tio.c_cc[VMIN] = 1;
    tio.c_cc[VTIME] = 5;

    cfsetospeed(&tio, B9600); //  baud
    cfsetispeed(&tio, B9600); //  baud

    tty_fd = open(argv[1], O_RDWR | O_NONBLOCK);
    exitOnFail(tty_fd < 0, "open")

    tcsetattr(tty_fd, TCSANOW, &tio);

    bool reqPend = false;
    bool delayPend = true;

    DataPoint value;

    KnowledgeSource myKS(BBTAG_TESTREAD);
    if (!myKS.connectKS())
        exit(1);

    while (true) {
        if (reqPend) {
            puts(">");
            value.clear();
            int ret = write(tty_fd, "A", 1);
            puts("A");
            exitOnFail((ret < 0) && (errno != EAGAIN) && (errno != EWOULDBLOCK), "write")

            if (ret == 1)
                reqPend = false;


            ret = tcdrain(tty_fd);
            exitOnFail(ret < 0, "tcflush")

        }

        if (delayPend) {
            puts("_");

            tv.tv_sec = 1;
            tv.tv_usec = 20000;
            select(0, 0, 0, 0, &tv);

            delayPend = false;
            reqPend = true;
        }

        //FD_ZERO(&fdr);
        //FD_SET(tty_fd, &fdr);
        //if (select(tty_fd + 1, &fdr, 0, 0, 0) == 1) {

        char ch;
        int ret = read(tty_fd, &ch, 1);
        exitOnFail((ret < 0) && (errno != EAGAIN) && (errno != EWOULDBLOCK), "read")
        if (ret == 1) {
            putchar(ch);
            if (ch == '\n') {
                myKS.update(value);
                delayPend = true;
            } else {
                value.push_back(ch);
            }
        }

        //} else {
        //    // something went wrong
        //    exit(1);
        //}
    }

    close(tty_fd);
}
