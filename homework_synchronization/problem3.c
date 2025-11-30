#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 8
int buffer[BUFFER_SIZE];
int in_pos = 0;
int out_pos = 0;
int p;
int c;
int k;
pthread_mutex_t buffer_mutex;
sem_t empty_slots;
sem_t full_slots;
int total=0;
int count;

void state()
{
	printf("The number of elements in the buffer: %d\n",count);
}

void *producer(void *arg)
{
	for(int i=0;i<k;i++)
	{
		sem_wait(&empty_slots);
		pthread_mutex_lock(&buffer_mutex);
		buffer[in_pos]=1;
		count++;
		in_pos=(in_pos+1)%BUFFER_SIZE;
		state();
		pthread_mutex_unlock(&buffer_mutex);
		sem_post(&full_slots);
	}
}

void *consumer(void *arg)
{
	while(true)
	{
		sem_wait(&full_slots);
		pthread_mutex_lock(&buffer_mutex);
		int read=buffer[out_pos];
		buffer[out_pos]=0;
		out_pos=(out_pos+1)%BUFFER_SIZE;
		if(count>0)
		{
			count--;
		}
		total++;
		if(total>=p*k)
		{
			state();
			pthread_mutex_unlock(&buffer_mutex);
			sem_post(&full_slots);
			break;
		}
		state();
		pthread_mutex_unlock(&buffer_mutex);
		sem_post(&empty_slots);
	}
}

int main()
{
	printf("Please, input the number of producers: ");
	scanf("%d", &p);
	printf("Please, input the number of items produced per producer: ");
	scanf("%d", &k);
	printf("Please, input the number of consumers: ");
        scanf("%d", &c);
	pthread_t *threads=malloc((p+c)*sizeof(pthread_t));
	if(threads==NULL)
	{
		perror("malloc failed");
                exit(1);
	}
	sem_init(&empty_slots, 0, BUFFER_SIZE);
	sem_init(&full_slots, 0, 0);
	pthread_mutex_init(&buffer_mutex, NULL);
	for(int i=0;i<p;i++)
	{
		if(pthread_create(&threads[i], NULL, producer, NULL)!=0)
		{
			perror("Failed to create thread");
			return 1;
		}
	}
	for(int i=0;i<c;i++)
	{
		if(pthread_create(&threads[p+i], NULL, consumer, NULL)!=0)
		{
			perror("Failed to create thread");
			return 1;
		}
	}
	for(int i=0;i<p+c;i++)
	{
		if(pthread_join(threads[i], NULL)!=0)
		{
			perror("failed to join thread");
			return 1;
		}
	}
	sem_destroy(&empty_slots);
	sem_destroy(&full_slots);
	free(threads);
	return 0;
}
