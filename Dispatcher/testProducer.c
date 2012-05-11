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
#include <stdlib.h>

typedef unsigned long long int u64;

typedef struct {
    u64 val;
    void* next;
} u64ll;

int main() {
    u64ll* primes = 0;
    u64ll* end = 0;

    // assume 2 is prime, it is
    primes = malloc(sizeof (u64ll));
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
            end->next = malloc(sizeof (u64ll));
            end = end->next;
            end->val = n;
            end->next = 0;
            fprintf(stderr, "[Prime] %lld\t%lld\n", ++count, n);
        }

        // there are no even primes
        n += 2;

    }
}

