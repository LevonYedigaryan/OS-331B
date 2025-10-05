#include <stdio.h>
#include <stdlib.h>

int main()
{
        int *arr=(int*)malloc(10*sizeof(int));
        if(arr==NULL)
        {
                perror("array creation error.");
                exit(1);
        }
        printf("Enter 10 integers: ");
        for(int i=0;i<10;i++)
        {
                scanf("%d", (arr+i));
        }
	arr=realloc(arr, 5*sizeof(int));
        printf("\nArray after resizing:");
        for(int i=0;i<5;i++)
        {
                printf(" %d", *(arr+i));
        }
	printf("\n");
        free(arr);
        arr=NULL;
        return 0;
}
