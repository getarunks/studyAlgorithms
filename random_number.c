#include <stdio.h>

#define GOLDEN_RATIO_64 0x61C8864680B583EBull

unsigned int hash_64_generic(unsigned long val, unsigned int bits)
{
	return val * GOLDEN_RATIO_64 >> (64 - bits);
}

int main(void)
{
	int a, b;

	printf("1 = %d\n", hash_64_generic(1, 3));
	printf("2 = %d\n", hash_64_generic(2, 3));
	printf("451 = %d\n", hash_64_generic(451, 3));
	printf("a = %p val = %d\n", &a, hash_64_generic(&a, 3));
	printf("a = %p val = %d\n", &b, hash_64_generic(&b, 3));
}
