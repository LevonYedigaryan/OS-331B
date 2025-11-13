#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* worker(void* arg)
{
        pthread_t current_thread_id = pthread_self();
        printf("Thread %lu is running\n", (unsigned long)current_thread_id);
        return NULL;
}

int main()
{
        pthread_t t1, t2, t3;
	pthread_t current_thread_id = pthread_self();
        printf("Main thread %lu is running\n", (unsigned long)current_thread_id);
	pthread_create(&t1, NULL, worker, (void*) NULL);
        pthread_create(&t2, NULL, worker, (void*) NULL);
	pthread_create(&t3, NULL, worker, (void*) NULL);
        pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
        return 0;
}
