#include <stdio.h>
#include <stddef.h>

#define MAX 5000

int flags[MAX];

int main(void)
{
	register int i, k, prime, count;

	for(i = 0; i < MAX; i++)
		flags[i] = TRUE;
	/* the first prime number is even. it is 2 */
	count = 1;
	/* find all odd prime numbers by sieving */
	for(i = 0; i < MAX; i++)
		if(flags[i])
		{
			prime = i + i + 3;
			for(k = i + prime; k < MAX; k += prime)
				flags[k] = FALSE;
			count++;
		}

	printf("n=%d\n", count);
	getchar();
	return(0);
}
