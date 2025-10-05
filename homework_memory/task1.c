#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n;
	printf("Enter the number of elements: ");
	scanf("%d", &n);
	printf("\n");
	int *arr=(int*)malloc(n*sizeof(int));
	if(arr==NULL)
	{
		perror("array creation error.");
		exit(1);
	}
	printf("Enter %d integers: ", n);
	for(int i=0;i<n;i++)
	{
		scanf("%d", (arr+i));
	}
	int m=0;
	for(int i=0;i<n;i++)
	{
		m=m+*(arr+i);
	}
	printf("\nSum of the array: %d\n", m);
	free(arr);
	arr=NULL;
	return 0;
}
