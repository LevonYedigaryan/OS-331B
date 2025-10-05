#include <stdio.h>
#include <stdlib.h>

int main()
{
        int n;
        printf("Enter the number of students: ");
        scanf("%d", &n);
        printf("\n");
        int *arr=(int*)malloc(n*sizeof(int));
        if(arr==NULL)
        {
                perror("array creation error.");
                exit(1);
        }
        printf("Enter the grades: ");
        for(int i=0;i<n;i++)
        {
                scanf("%d", (arr+i));
        }
        int max=*arr;
	int min=*arr;
        for(int i=0;i<n;i++)
        {
		if(*(arr+i)>max)
		{
			max=*(arr+i);
		}
		if(*(arr+i)<min)
		{
			min=*(arr+i);
		}
        }
        printf("\nHighest grade: %d\nLowest grade: %d\n", max, min);
        free(arr);
        arr=NULL;
        return 0;
}
