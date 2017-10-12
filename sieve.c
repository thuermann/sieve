/*
 * $Id: sieve.c,v 1.7 2017/10/12 08:51:31 urs Exp $
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <limits.h>

typedef uintmax_t int_t;
#define PRI PRIuMAX

static char *alloc(int_t n);
static void set(char *s, int_t n);
static int test(const char *s, int_t n);
static int_t sieve(char *s, int_t n);

static void usage(const char *name)
{
	fprintf(stderr, "Usage: %s [-v] number\n", name);
}

int main(int argc, char **argv)
{
	char *name = argv[0];
	int verbose = 0;
	int_t n, i;
	int_t count;
	char *s;

	if (argc > 1 && strcmp(argv[1], "-v") == 0) {
		verbose = 1;
		argc--, argv++;
	}
	if (argc != 2) {
		usage(name);
		exit(1);
	}

	/* The sieve is a bit array with one bit for each odd number n
	 * above 2, i.e. bit i is for n = 2 * i + 3.  Thus, we need
	 * (n-3)/2 + 1 bits to find primes up to and including n.
	 */
	n = strtoull(argv[1], NULL, 0);
	n = (n - 3) / 2 + 1;

	if (!(s = alloc(n))) {
		perror("malloc");
		exit(1);
	}
	count = sieve(s, n);
	printf("n = %"PRI"\n", count);
	if (verbose) {
		puts("2");
		for (i = 0; i < n; i++)
			if (!test(s, i))
				printf("%"PRI"\n", 2 * i + 3);
	}
	free(s);

	return 0;
}

static int_t sieve(char *s, int_t n)
{
	int_t i, k, prime;
	int_t count;

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

static char *alloc(int_t n)
{
	return calloc((n + CHAR_BIT - 1) / CHAR_BIT, 1);
}

static void set(char *s, int_t n)
{
	int_t chr = n / CHAR_BIT;
	int   bit = n % CHAR_BIT;
	s[chr] |= 1 << bit;
}

static int test(const char *s, int_t n)
{
	int_t chr = n / CHAR_BIT;
	int   bit = n % CHAR_BIT;
	return (s[chr] >> bit) & 1;
}
