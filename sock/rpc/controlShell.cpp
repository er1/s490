#include "controlShell.h"

controlShell::controlShell()
{
}

controlShell::controlShell(uint32_t t)
{
}

void controlShell::init()
{
    struct sockaddr_un remote;

	memset(&buf, 0, BUFFSIZE - 1);

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    printf("Trying to connect...\n");

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, CS_SOCK_PATH);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("connect");
        exit(1);
    }

    printf("Connected.\n");
}

void controlShell::reg(uint32_t t)
{
}

void controlShell::getLast(dataPoint * dp)
{
}

void controlShell::getLast(uint32_t n, vector<dataPoint> * dpVect)
{
}
