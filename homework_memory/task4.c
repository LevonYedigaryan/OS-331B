#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
        char **arr=(char**)malloc(3*sizeof(char*));
        if(arr==NULL)
        {
                perror("array creation error.");
                exit(1);
        }
	printf("Enter 3 strings: ");
	for(int i=0;i<3;i++)
	{
		*(arr+i)=(char*)malloc(50*sizeof(char));
		if(*(arr+i)==NULL)
        	{
			perror("string creation error.");
                	exit(1);
        	}
		scanf("%50s", *(arr+i));
	}
	arr=realloc(arr, (3+2)*sizeof(char*));
	printf("\nEnter 2 more strings: ");
	for(int i=0;i<2;i++)
        {
                *(arr+3+i)=(char*)malloc(50*sizeof(char));
                if(*(arr+i)==NULL)
                {
                        perror("string creation error.");
                        exit(1);
                }
                scanf("%50s", *(arr+3+i));
        }
	printf("\nAll strings:");
        for(int i=0;i<5;i++)
        {
                printf(" %s", *(arr+i));
        }
	for(int i=0;i<5;i++)
	{
		free(*(arr+i));
		*(arr+i)=NULL;
	}
        free(arr);
        arr=NULL;
	printf("\n");
        return 0;
}    
