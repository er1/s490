#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "common.h"

double aquire_sample();

int main() {

	while (1) {
		double point, t;
	
		point = aquire_sample();

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
	delay(rand() % 100 * 1000000);

	// generate a sample and return it
	p = (p + 27) % 1024;
	point = cos(p * PI / 512);
	return point;
}

