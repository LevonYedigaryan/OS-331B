#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

long long balance=0;
int n;
pthread_mutex_t mut;
pthread_spinlock_t sp;
time_t start;

void result(char* lock, int mode)
{
	char* m;
	if(mode ==0)
	{
		m="long";
	}
	else
	{
		m="short";
	}
	time_t end=time(NULL);
	double runtime=difftime(end, start);
	printf(
	        "Using %s with %s critical section\n"
	        "Final balance: %lld\n"
	        "Runtime: %.3f seconds\n",
	        lock, m, balance, runtime
	);
}

void read_input()
{
	printf("Please input the number of operations: ");
	scanf("%d", &n);
}

void* inc_m(void* arg)
{
	pthread_mutex_lock(&mut);
        balance++;
	int mode=*(int*)arg;
	if(mode==0)
        {
                usleep(100);
        }
	pthread_mutex_unlock(&mut);
}

void* dec_m(void* arg)
{
        pthread_mutex_lock(&mut);
        balance--;
        int mode=*(int*)arg;
        if(mode==0)
        {
                usleep(100);
        }
        pthread_mutex_unlock(&mut);
}

void mutex()
{
	read_input();
	pthread_t *threads=malloc(2*n*sizeof(pthread_t));
	if(threads==NULL)
        {
                perror("malloc failed");
                exit(1);
        }
	pthread_mutex_init(&mut, NULL);
	for(int mode =0;mode<2;mode++)
	{
		for(int i=0;i<n;i++)
		{
			if(pthread_create(&threads[2*i], NULL, inc_m, &mode)!=0)
			{
				perror("Failed to create thread");
				exit(1);
			}
			if(pthread_create(&threads[2*i+1], NULL, dec_m, &mode)!=0)
                        {
                                perror("Failed to create thread");
				exit(1);
                        }
		}
		for(int i=0;i<2*n;i++)
		{
			if(pthread_join(threads[i], NULL)!=0)
			{
				perror("Failed to join thread");
				exit(1);
			}
		}
		pthread_mutex_destroy(&mut);
		result("Mutex", mode);
		balance=0;
	}
	free(threads);
}

void* inc_s(void* arg)
{
        pthread_spin_lock(&sp);
        balance++;
	int mode=*(int*)arg;
        if(mode==0)
	{
		usleep(100);
	}
        pthread_spin_unlock(&sp);
}

void* dec_s(void* arg)
{
        pthread_spin_lock(&sp);
        balance--;
        int mode=*(int*)arg;
        if(mode==0)
        {
                usleep(100);
        }
        pthread_spin_unlock(&sp);
}

void spin()
{
	read_input();
	pthread_t *threads=malloc(2*n*sizeof(pthread_t));
	if(threads==NULL)
	{
		perror("malloc failed");
		exit(1);
	}
        pthread_spin_init(&sp, PTHREAD_PROCESS_PRIVATE);
	for(int mode=0;mode<2;mode++)
	{
        	for(int i=0;i<n;i++)
        	{
        	        if(pthread_create(&threads[2*i], NULL, inc_s, &mode)!=0)
        	        {
        	                perror("Failed to create thread");
				exit(1);
        	        }
			if(pthread_create(&threads[2*i+1], NULL, dec_s, &mode)!=0)
                        {
                                perror("Failed to create thread");
				exit(1);
                        }
        	}
        	for(int i=0;i<2*n;i++)
        	{
        	        if(pthread_join(threads[i], NULL)!=0)
        	        {
        	                perror("Failed to join thread");
				exit(1);
        	        }
		}
		pthread_spin_destroy(&sp);
		result("Spinlock", mode);
		balance=0;
        }
	free(threads);
}

int main(int argsl, char *args[])
{
	if(argsl!=2)
	{
		printf("Error: should be 1 argument.\n");
		return 1;
	}
	start=time(NULL);
	if (strcmp(args[1], "mutex") == 0) {
		mutex();
	}
	else if (strcmp(args[1], "spin") == 0) {
		spin();
	}
	else
	{
		printf("Error: Incorrect format of the argument\n");
		return 1;
	}
	return 0;
}
