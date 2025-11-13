#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int a[20];

void* worker(void* arg)
{
	int st = *(int*)arg;
	int sum=0;
        for(int i=0;i<10;i++)
	{
		sum=sum+a[i+st];
	}
        printf("The sum of the 10 elements starting from the index %d is: %d \n", st, sum);
        return NULL;
}

int main()
{
	for(int i=0;i<20;i++)
	{
		a[i]=i;
	}
        pthread_t t1, t2;
	int start1=0, start2=10;
        pthread_create(&t1, NULL, worker, &start1);
        pthread_create(&t2, NULL, worker, &start2);
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        return 0;
}
