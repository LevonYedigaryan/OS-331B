#include <stdio.h>
#include <stdlib.h>

int main()
{
        int n;
        printf("Enter the number of elements: ");
        scanf("%d", &n);
        int *arr=(int*)calloc(n, sizeof(int));
        if(arr==NULL)
        {
                perror("array creation error.");
                exit(1);
        }
	printf("\nArray after calloc:");
	for(int i=0;i<n;i++)
	{
		printf(" %d", *(arr+i));
	}
        printf("\nEnter %d integers: ", n);
        for(int i=0;i<n;i++)
        {
                scanf("%d", (arr+i));
        }
	printf("\nUpdated array:");
        for(int i=0;i<n;i++)
        {
                printf(" %d", *(arr+i));
        }
        int m=0;
        for(int i=0;i<n;i++)
        {
                m=m+*(arr+i);
        }
	float a=(float)m/n;
        printf("\nAverage of the array: %.1f\n", a);
	free(arr);
	arr=NULL;
        return 0;
}
