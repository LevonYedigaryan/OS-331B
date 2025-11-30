#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int p;
int j;
int counter;
pthread_mutex_t mut;
sem_t printers;

void *print(void *arg)
{
	int i = (int)(long)arg;
	sem_wait(&printers);
	pthread_mutex_lock(&mut);
	counter++;
	printf("Thread %d is printing.\nNumber of working printers: %d\n",i,counter);
	pthread_mutex_unlock(&mut);
	usleep(1000);
	pthread_mutex_lock(&mut);
        counter--;
        pthread_mutex_unlock(&mut);
	sem_post(&printers);
}

int main()
{
	printf("Please, input the number of printers: ");
	scanf("%d", &p);
	printf("Please, input the number of jobs: ");
	scanf("%d", &j);
	pthread_t *threads=malloc(j*sizeof(pthread_t));
	if(threads==NULL)
        {
                perror("malloc failed");
                exit(1);
        }
	sem_init(&printers, 0, p);
	pthread_mutex_init(&mut, NULL);
	for(int i=0;i<j;i++)
	{
		if(pthread_create(&threads[i], NULL, print, (void*)(long)i)!=0)
		{
			perror("Failed to create thread");
			exit(1);
		}
	}
	for(int i=0;i<j;i++)
	{
		if(pthread_join(threads[i], NULL)!=0)
		{
			perror("failed to join thread");
			exit(1);
		}
	}
	sem_destroy(&printers);
	free(threads);
	return 0;
}
