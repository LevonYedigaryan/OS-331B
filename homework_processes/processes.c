#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <sys/wait.h>
void prog1()
{
	printf("first function called.\n");
}
void prog2()
{
	printf("second function called.\n");
}
int main() 
{
	printf("Task1########################################################\n");
	pid_t pid1;
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (pid1 == 0)
	{	
		printf("Child PID:%d\n", getpid());
		exit(0);
	}	
	else
		printf("Parent PID:%d\n", getpid());
	printf("Task2########################################################\n");
	pid_t pid21, pid22;
        pid21 = fork();
        if (pid21 < 0)
        {
                perror("Fork failed");
                exit(1);
        }
        else if (pid21 == 0)
        {
                printf("Child PID:%d\n", getpid());
                exit(0);
        }
        else
	{
		pid22=fork();
		if(pid22<0)
		{
			perror("Fork failed");
			exit(1);
		}
		else if(pid22==0)
		{
			printf("Child PID:%d\n", getpid());
                	exit(0);
		}
		else
		{
			waitpid(pid22, NULL, 0);
			printf("Second child finished.\n");
                	wait(NULL);
                	printf("First child finished.\n");
                	printf("Parent PID:%d\n", getpid());
		}
	}
	printf("Task3########################################################\n");
	//atexit(prog1);
	//atexit(prog2);
	printf("main maining.\n");
	//exit(0); //sorry had to comment this thing out otherwise the Tasks 4 and 5 wouldn't run. to test everything you may remove the comments before the atexit and exit commands;
	printf("Task4########################################################\n");
	pid_t pid31, pid32;
	int status;
        pid31 = fork();
        if (pid31 < 0)
        {
                perror("Fork failed");
                exit(1);
        }
        else if (pid31 == 0)
        {
                printf("Child PID:%d\nExit Status: 0\n", getpid());
                exit(0);
        }
        else
        {
                pid32=fork();
                if(pid32<0)
                {
                        perror("Fork failed");
                        exit(1);
                }
                else if(pid32==0)
                {
                        printf("Child PID:%d\nExit Status 3\n", getpid());
                        exit(3);
                }
                else
                {
                        waitpid(pid31, &status, 0);
			if(WIFEXITED(status))
			{
				printf("Child exited with status%d\n", WEXITSTATUS(status));
			}
			waitpid(pid32, &status, 0);
			if(WIFEXITED(status))
                        {
                                printf("Child exited with status%d\n", WEXITSTATUS(status));
                       	}
			printf("Parent PID:%d\n", getpid());
		}
	}
	printf("Task5########################################################\nWithout wait()\n");
	pid_t pid41;
        pid41 = fork();
        if (pid41 < 0)
        {
                perror("Fork failed");
                exit(1);
        }
        else if (pid41 == 0)
        {
                printf("Child PID:%d\n", getpid());
                exit(0);
        }
        else
        {
		printf("States without wait:\n");
                //execl("/bin/ps", "ps", "-l", NULL);
		printf("States with wait():\n");
		wait(NULL);
		//execl("/bin/ps", "ps", "-l", NULL); //as execl "reclaces" the program and anything after it never runs I had to comment those out. to check each output remove the comments before the corresponding execl and it works.
		exit(0);
	}
	return 0;
} 
