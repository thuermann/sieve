/*
 * $Id: sieve.c,v 1.5 2012/05/01 06:00:29 urs Exp $
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/* The sieve is a bit array with one bit for each odd number above 2,
 * i.e. bit i is for 2 * i + 3.  We provide space for 5000 flags,
 * i.e. for prime numbers up to 4999 * 2 + 3 = 10001.
 */
#define MAX 5000

static char *alloc(unsigned int n);
static void set(char *s, unsigned int n);
static int test(const char *s, unsigned int n);
static int sieve(char *s, unsigned int n);

int main(void)
{
	unsigned int n = MAX;
	int count;
	char *s;

	if (!(s = alloc(n))) {
		perror("malloc");
		exit(1);
	}
	count = sieve(s, n);
	printf("n = %d\n", count);
	free(s);

	return 0;
}

static int sieve(char *s, unsigned int n)
{
	unsigned int i, k, prime;
	int count;

	/* The first prime number is even. It is 2. */
	count = 1;

	/* Find all odd prime numbers by sieving. */
	for (i = 0; i < n; i++)
		if (!test(s, i)) {
			prime = 2 * i + 3;
			/* Discard all odd multiples of prime. */
			for (k = i + prime; k < n; k += prime)
				set(s, k);
			count++;
		}

	return count;
}

static char *alloc(unsigned int n)
{
	return calloc((n + CHAR_BIT - 1) / CHAR_BIT, 1);
}

static void set(char *s, unsigned int n)
{
	int chr = n / CHAR_BIT;
	int bit = n % CHAR_BIT;
	s[chr] |= 1 << bit;
}

static int test(const char *s, unsigned int n)
{
	int chr = n / CHAR_BIT;
	int bit = n % CHAR_BIT;
	return (s[chr] >> bit) & 1;
}
