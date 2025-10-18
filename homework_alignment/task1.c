#include <stdio.h>

int main()
{
	int i;
	char c;
	double d;
	short s;
	printf("Size of int: %ld\nSize of char: %ld\nSize of double: %ld\nSize of short: %ld\n", sizeof(i), sizeof(c), sizeof(d), sizeof(s));
	printf("Address of int: %p\nAddress of char: %p\nAddress of double: %p\nAddress of short: %p\n", &i, &c, &d, &s);
	return 0;
}
