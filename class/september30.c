#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("SIZEOF//////////////////////////////////////////////////////////////////\n");
	printf("integer: %ld\nchar: %ld\ndouble: %ld\n", sizeof(int), sizeof(char), sizeof(double));
	printf("MALLOC//////////////////////////////////////////////////////////////////\n");
	int *arr;
	int n;
	scanf("%d", &n);
	arr=(int*)malloc(n*sizeof(int));
	if(arr==NULL)
	{

		perror("");
		exit(0);
	}
	printf("printings the array:\n");
	for(int i=0;i<n;i++)
	{
		arr[i]=i;
		printf("%d\n", arr[i]);
	}
	free(arr);
	int *ptr=(int*)malloc(sizeof(int));
	*ptr=7;
	printf("ptr address is: %p\nptr value is: %d\n", ptr, *ptr);
	free(ptr);
	printf("ptr address is: %p\nptr value is: %d\n", ptr, *ptr);
	*ptr=42;
	printf("ptr address is: %p\nptr value is: %d\n", ptr, *ptr);
	ptr=NULL;
	return 0;
}
