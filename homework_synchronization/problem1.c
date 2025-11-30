#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long counter=0;
int n;
int m;
pthread_mutex_t mut;
pthread_spinlock_t sp;

void result()
{
	long long e=((long long)m)*n;
	printf("Expected: %lld\nActual: %lld\n", e, counter);
}

void read()
{
	printf("Please input the number of threads: ");
	scanf("%d", &n);
	printf("Please input the increment amount: ");
        scanf("%d", &m);
}

void* count(void* arg)
{
	for(int i=0;i<m;i++)
	{
		counter++;
	}
}

void def()
{
	read();
	pthread_t *threads=malloc(n*sizeof(pthread_t));
	if(threads==NULL)
        {
                perror("malloc failed");
                exit(1);
        }
	for(int i=0;i<n;i++)
	{
		if(pthread_create(&threads[i], NULL, count, NULL)!=0)
		{
                        perror("Failed to create thread");
			exit(1);
		}
	}
	for(int i=0;i<n;i++)
	{
		if(pthread_join(threads[i], NULL)!=0)
		{
			perror("Failed to join thread");
			exit(1);
		}
	}
	free(threads);
}

void* count_m(void* arg)
{
	for(int i=0;i<m;i++)
        {
		pthread_mutex_lock(&mut);
                counter++;
		pthread_mutex_unlock(&mut);
        }
}

void mutex()
{
	read();
	pthread_t *threads=malloc(n*sizeof(pthread_t));
	if(threads==NULL)
        {
                perror("malloc failed");
                exit(1);
        }
	pthread_mutex_init(&mut, NULL);
	for(int i=0;i<n;i++)
	{
		if(pthread_create(&threads[i], NULL, count_m, NULL)!=0)
		{
			perror("Failed to create thread");
			exit(1);
		}
	}
	for(int i=0;i<n;i++)
	{
		if(pthread_join(threads[i], NULL)!=0)
		{
			perror("Failed to join thread");
			exit(1);
		}

	}
	pthread_mutex_destroy(&mut);
	free(threads);
}

void* count_s(void* arg)
{
        for(int i=0;i<m;i++)
        {
                pthread_spin_lock(&sp);
                counter++;
                pthread_spin_unlock(&sp);
        }
}

void spin()
{
	read();
	pthread_t *threads=malloc(n*sizeof(pthread_t));
	if(threads==NULL)
	{
		perror("malloc failed");
		exit(1);
	}
        pthread_spin_init(&sp, PTHREAD_PROCESS_PRIVATE);
        for(int i=0;i<n;i++)
        {
                if(pthread_create(&threads[i], NULL, count_s, NULL)!=0)
                {
                        perror("Failed to create thread");
			exit(1);
                }
        }
        for(int i=0;i<n;i++)
        {
                if(pthread_join(threads[i], NULL)!=0)
                {
                        perror("Failed to join thread");
			exit(1);
                }

        }
        pthread_spin_destroy(&sp);
	free(threads);
}

int main(int argsl, char *args[])
{
	pthread_t threads[5];
	if(argsl!=2)
	{
		printf("Error: should be 1 argument.\n");
		return 1;
	}
	switch(args[1][0])
	{
		case 'A':
			def();
			break;
		case 'B':
			mutex();
			break;
		case 'C':
			spin();
			break;
		default:
			printf("Error: Incorrect format of the argument\n");
			return 1;
	}
	result();
	return 0;
}
