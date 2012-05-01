/*
 * $Id: sieve.c,v 1.3 2012/05/01 05:58:11 urs Exp $
 */

#include <stdio.h>

#define MAX 5000

static int flags[MAX];

int main(void)
{
	int i, k, prime, count;

	for (i = 0; i < MAX; i++)
		flags[i] = 1;

	/* The first prime number is even. It is 2. */
	count = 1;

	/* Find all odd prime numbers by sieving. */
	for (i = 0; i < MAX; i++)
		if (flags[i]) {
			prime = 2 * i + 3;
			for (k = i + prime; k < MAX; k += prime)
				flags[k] = 0;
			count++;
		}

	printf("n=%d\n", count);

	return 0;
}
