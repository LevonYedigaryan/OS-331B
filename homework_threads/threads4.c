#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* worker(void* arg)
{
	int num=*(int*)arg;
	int square=num*num;
        printf("The square of %d is %d\n", num, square);
        return NULL;
}

int main()
{
	int a[]={1, 2, 3, 4, 5};
        pthread_t t[5];
	for(int i=0;i<5;i++)
	{
		pthread_create(&t[i], NULL, worker, &a[i]);
	}
        for(int i=0;i<5;i++)
	{
		pthread_join(t[i], NULL);
	}
        return 0;
}
