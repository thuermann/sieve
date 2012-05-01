/*
 * $Id: sieve.c,v 1.4 2012/05/01 05:59:34 urs Exp $
 */

#include <stdio.h>

/* The array to hold the sieve.  There's a flag for each odd number
 * above 2, i.e. flag[i] is for 2 * i + 3.  We provide space for 5000
 * flags, i.e. for prime numbers up to 4999 * 2 + 3 = 10001.
 */
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
			/* Discard all odd multiples of prime. */
			for (k = i + prime; k < MAX; k += prime)
				flags[k] = 0;
			count++;
		}

	printf("n=%d\n", count);

	return 0;
}
