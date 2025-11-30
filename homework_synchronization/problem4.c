#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int n;
sem_t semA, semB, semC;

void *thread_A(void *arg)
{
	for(int i=0;i<n;i++)
	{
		sem_wait(&semA);
		printf("Thread A: %d\n", i);
		sem_post(&semB);
	}
}

void *thread_B(void *arg)
{
        for(int i=0;i<n;i++)
        {
                sem_wait(&semB);
                printf("Thread B: %d\n", i);
                sem_post(&semC);
        }
}

void *thread_C(void *arg)
{
        for(int i=0;i<n;i++)
        {
                sem_wait(&semC);
                printf("Thread C: %d\n", i);
                sem_post(&semA);
        }
}

int main()
{
	printf("Please, input the number of iterations: ");
	scanf("%d", &n);
	pthread_t threads[3];
	sem_init(&semA, 0, 1);
	sem_init(&semB, 0, 0);
	sem_init(&semC, 0, 0);
	if(pthread_create(&threads[0], NULL, thread_A, NULL)!=0)
	{
		perror("Failed to create thread");
		return 1;
	}
	if(pthread_create(&threads[1], NULL, thread_B, NULL)!=0)
        {
                perror("Failed to create thread");
		return 1;
        }
	if(pthread_create(&threads[2], NULL, thread_C, NULL)!=0)
        {
                perror("Failed to create thread");
		return 1;
        }
	for(int i=0;i<3;i++)
	{
		if(pthread_join(threads[i], NULL)!=0)
		{
			perror("failed to join thread");
			return 1;
		}
	}
	sem_destroy(&semA);
	sem_destroy(&semB);
	sem_destroy(&semC);
	return 0;
}
