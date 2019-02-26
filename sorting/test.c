int value(int *i)
{
	*i = 11;
	return *i++;
}
int main()
{
	int i = 10;
	printf("%d\n", value(&i));
	printf("%d\n", i);
}
