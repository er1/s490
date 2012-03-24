#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <common/common.h>

double aquire_sample();

struct sigaction* sig_usr1;

int usr1_called = 0;

void sig_usr1_handler(int signal) {
    usr1_called++;
}

int main() {

    log("Starting READ\n");

    log("Registering USR1 Handler\n");

    // create space for sig_usr1
    sig_usr1 = malloc(sizeof (struct sigaction));
    // TODO: fail on malloc fail;

    // define it
    sig_usr1->sa_handler = sig_usr1_handler;
    sig_usr1->sa_flags = 0;
    sigemptyset(&sig_usr1->sa_mask);

    // create the handler
    sigaction(SIGUSR1, sig_usr1, NULL);

    log("[Read]: Start!\n");

    while (1) {
        double point, t;

        point = aquire_sample();

        if (usr1_called) {
            log("[Read]: USR1\n");
            break;
        }

        printf("[Read]: ");

        for (t = -1; t < point; t += 1.0 / 32) {
            putchar(' ');
        }

        printf("+\n");
    }


    return 0;
}

double aquire_sample() {
    // keep last sample reference
    static short int p = 0;
    double point;

    // simulate a blocking read delay
    //delay(rand() % 100 * 1000000);

    // generate a sample and return it
    p = (p + 27) % 1024;
    point = cos(p * PI / 512);
    return point;
}

