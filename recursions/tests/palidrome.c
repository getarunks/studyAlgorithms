#include<stdio.h>
#include <string.h>

int isPalidrome(char *str, int len)
{
	if (len == 1 )
		return 1;

	if (str[0] != str[len - 1])
		return 0;

	return isPalidrome(str + 1, len - 2);
}

int main(void)
{
	//char *str = "madam";
	char *str = "amadama";
	printf("Is %s palidrom = %d\n", str, isPalidrome(str, strlen(str)));
}
