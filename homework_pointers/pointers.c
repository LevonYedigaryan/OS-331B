#include <stdio.h>

void swap(int *a, int *b)
{
	*b = *a + *b;
	*a = *b - *a;
	*b = *b - *a;
}

int main()
{
	printf("TASK 1==============================================================\n");
	int kakadu = 10;
	int *ptr = &kakadu;
	printf("Address using variable: %p\n", &kakadu);
	printf("Address using pointer: %p\n", ptr);
	*ptr = 100;
	printf("Value after modification, using variable: %d\n", kakadu);
        printf("Value after modification, using pointer: %d\n", *ptr);
	printf("TASK 2==============================================================\n");
	int a[5]={1, 2, 3, 4, 5};
	int *ptrArray = a;
	for(int i=0;i<5;i++)
	{
		*(ptrArray + i) = *(ptrArray + i) + 157;
	}
	printf("Using the array name: ");
	for(int i=0;i<5;i++)
	{
		printf("%d", a[i]);
		if(i<4)
		{
			printf(", ");
		}
	}
	printf("\n");
	printf("Using the pointer name: ");
        for(int i=0;i<5;i++)
        {
                printf("%d", *(ptrArray + i));
                if(i<4)
                {
                        printf(", ");
                }
        }
	printf("\n");
	printf("TASK 3==============================================================\n");
	int first = 15;
	int second = 341;
	int *ptrFirst = &first;
	int *ptrSecond = &second;
	printf("Before: x=%d, y=%d\n", first, second);
	swap( ptrFirst, ptrSecond);
	printf("After: x=%d, y=%d\n", first, second);
	printf("TASK 4==============================================================\n");
	int dzmeruk = 5728;
	int *ptrDzmeruk = &dzmeruk;
	int **ptrptrDzmeruk = &ptrDzmeruk;
	printf("Using pointer: %d\n", *ptrDzmeruk);
	printf("Using pointer's pointer: %d\n", **ptrptrDzmeruk);
	printf("TASK 5==============================================================\n");
	char str[] = "Hello";
	char *ptrString = str;
	int length = 0;
	printf("The text is: ");
	while(*(ptrString + length) != '\0')
	{
		printf("%c", *(ptrString + length));
		length = length + 1;
	}
	printf("\nThe length of the text is: %d\n", length);
}
