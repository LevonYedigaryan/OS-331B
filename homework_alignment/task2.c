#include <stdio.h>

struct Struct
{
	char a;
	int b;
	double c;
};

struct Struct2
{
        double c;
	int a;
	char b;
};

int main()
{
	struct Struct2 str2;
	struct Struct str;
	printf("Size of the struct is: %ld\nAddress of char: %p\nAddress of int: %p\nAddress of double: %p\n", sizeof(str), &str.a, &str.b, &str.c);
	printf("Size of the struct after changes is: %ld\nAddress of char after changes: %p\nAddress of int after changes: %p\nAddress of double after changes: %p\n", sizeof(str2), &str2.a, &str2.b, &str2.c);
	printf("No changing the size the order of variables doesn't affect the size of the struct however the padding because of the natural allignment makes the struct'bigger than necessary', as it shows 16 but char int and double only requre 13 bytes.\n");
	return 0;
}
