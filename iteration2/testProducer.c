#include <stdio.h>
#include <stdlib.h>
#include "common.h"

typedef unsigned long long int u64;
typedef struct {
	u64 val;
	void* next;
} u64ll;

int main() {
	u64ll* primes = 0;
	u64ll* end = 0;

	// assume 2 is prime, it is
	primes = malloc(sizeof(u64ll));
	primes->val = 2;
	primes->next = 0;
	end = primes;
	
	//printf("1\t2\n");

	// start at 3
	u64 n = 3;
	u64 count = 1;	

	for (;;) {
		int prime = 1;
		u64ll* it;

		// loop over primes
		for (it = primes; it; it = it->next) {
			// sqrt(n) < current prime --> n is prime
			if ((it->val * it->val) > n)
				break;

			// n mod current prime --> n is not prime
			if (n % it->val == 0) {
				prime = 0;
				break;
			}
		}

		// keep and print the prime
		if (prime) {
			end->next = malloc(sizeof(u64ll));
			end = end->next;
			end->val = n;
			end->next = 0;
			fprintf(stderr, "[Prime] %lld\t%lld\n", ++count, n);
		}

		// there are no even primes
		n += 2;

	}
}

