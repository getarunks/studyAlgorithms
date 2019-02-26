#include <stdio.h>

int isPermutation(char *str1, int len1, char *str2, int len2)
{
	int i, total=0;
	if (len1 != len2)
		return 0;

	for(i = 0 ; i < len1; i++)
		total += str1[i];

	for (i = 0 ; i < len2; i++)
		total -= str2[i];

	if (total == 0)
		return 1;
	else
		return 0;
}

int main(void)
{
	printf("is permutation = %d\n", isPermutation("arua", 4, "runa", 4));
}
