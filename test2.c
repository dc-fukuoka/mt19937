#include <stdio.h>
#include <stdlib.h>

/* 64 bits MT19937
 * http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/ARTICLES/mt.pdf
 */

/* constants */
#define W 64
#define N 312
#define M 156
#define R 31

#define U 29
#define S 17
#define T 37
#define L 43

#define A 0xb5026f5aa96619e9UL
#define B 0x71d67fffeda60000UL
#define C 0xfff7eee000000000UL
#define D 0x5555555555555555UL

#define UPPER_MASK 0xffffffff80000000UL /* upper W-R bits */
#define LOWER_MASK 0x7fffffffUL /* lower R bits */

#define F 6364136223846793005UL

static unsigned long int x[N] = {0UL};

void init_mt(int seed)
{
	int i;
	
	x[0] = seed;
	for (i=1; i<N; i++)
		x[i] = F*(x[i-1] ^ (x[i-1] >> (W-2))) + i;
}

unsigned long int gen_rand(void)
{
	static int k = 0; /* need to keep it */
	unsigned long int y, z;

	/* z = (x^u_k | x^l_(k+1))*/
	z    = (x[k] & UPPER_MASK) | (x[(k+1)%N] & LOWER_MASK);
	/* x_(k+n) = x_(k+m) |+| z*A */
	x[k] = x[(k+M)%N] ^ (z >> 1) ^ ((z == 1UL) ? 0UL : A);
	/* Tempering */
	y    = x[k];
	y   ^= ((y >> U) & D);
	y   ^= ((y << S) & B);
	y   ^= ((y << T) & C);
	y   ^=  (y >> L);

	k = (k + 1)%N;
	return y;
}

int main(int argc, char **argv)
{
	int i;
	int seed = (argc == 1) ? 7777 : atoi(argv[1]);
	
	printf("seed: %d\n", seed);

	init_mt(seed);
	for (i=0; i<1000; i++)
		printf("%20lu\n", gen_rand());
	
	return 0;
}
