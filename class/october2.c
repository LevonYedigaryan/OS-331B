#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num;
	scanf("%d", &num);
	int *arr=(int*)calloc(num, sizeof(int));
	if(arr==NULL)
        {
                perror("");
                exit(0);
        }
	printf("%d\n", arr[0]);
	arr[0]=5;
	printf("%d\n", arr[0]);
	arr=NULL;
	free(arr);
	return 0;
}
