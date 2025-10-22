#include <stdio.h>
#include <stdlib.h>

struct Process
{
	int pid;
	int arrival_time;
	int burst_time;
	int turnaround_time;
	int waiting_time;
	int response_time;
};

void FCFS(struct Process processes[], int length)
{
	for(int i=0;i<length-1;i++)
	{
		for(int j=i+1;j<length-i-1;j++)
		{
			if(processes[j+1].arrival_time<processes[j].arrival_time)
			{
				struct Process k=processes[j];
				processes[j]=processes[j+1];
				processes[j+1]=k;
			}			
		}
	}
	printf("=== First Come First Served (FCFS) ===\nGantt Chart: ");
	for(int i=0;i<length;i++)
	{
		printf("| P%d ", processes[i].pid);
	}
	printf("|\nPID\tAT\tBT\tWT\tTAT\tRT\n");
	int time=0, wait=0, tat=0, rt=0;
	for(int i=0;i<length;i++)
	{
		processes[i].turnaround_time=time+processes[i].burst_time-processes[i].arrival_time;
		processes[i].waiting_time=time-processes[i].arrival_time;
		processes[i].response_time=time-processes[i].arrival_time;
		time=time+processes[i].burst_time;
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time, processes[i].response_time);
		wait=wait+processes[i].waiting_time;
		tat=tat+processes[i].turnaround_time;
		rt=rt+processes[i].response_time;
	}
	printf("\nAverage Waiting Time: %.2f\nAverage Turnaround Time: %.2f\nAverage Response Time: %.2f\n", (float)wait/length, (float)tat/length, (float)rt/length);
}

void SJF(struct Process processes[], int length)
{
	printf("=== Shortest Job FIrst (SJF) ===\nGantt Chart: ");
	for(int i=0;i<length-1;i++)
        {
                for(int j=i+1;j<length-i-1;j++)
                {
                        if(processes[j+1].arrival_time<processes[j].arrival_time)
                        {
                                struct Process k=processes[j];
                                processes[j]=processes[j+1];
                                processes[j+1]=k;
                        }
                }
	}
	int time=0, min=processes[0].burst_time, wait=0, tat=0, rt=0;
	int all_time=0;
	for(int i=0;i<length;i++)
	{
		all_time=all_time+processes[i].burst_time;
	}
	while(time<all_time)
	{
		int pr;
		for(int i=0;i<length;i++)
		{
			if(processes[i].arrival_time<=time)
                	{
				if(processes[i].burst_time<min)
				{
					min=processes[i].burst_time;
					pr=i;
				}
				else if(processes[i].burst_time==min)
				{
					if(processes[i].arrival_time<processes[pr].arrival_time)
					{
						pr=i;
					}
				}
			}
             	}
		processes[pr].turnaround_time=time+processes[pr].burst_time-processes[pr].arrival_time;
		processes[pr].waiting_time=time-processes[pr].arrival_time;
		processes[pr].response_time=time-processes[pr].arrival_time;
		time=time+processes[pr].burst_time+1;
		printf("| P%d ", processes[pr].pid);
		wait=wait+processes[pr].waiting_time;
                tat=tat+processes[pr].turnaround_time;
                rt=rt+processes[pr].response_time;

	}
	printf("|\nPID\tAT\tBT\tWT\tTAT\tRT\n");
	for(int i=0;i<length;i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time, processes[i].response_time);
	}
	printf("\nAverage Waiting Time: %.2f\nAverage Turnaround Time: %.2f\nAverage Response Time: %.2f\n", (float)wait/length, (float)tat/length, (float)rt/length);
}

int main()
{
	int length;
	printf("Enter the number of processes: ");
	scanf("%d", &length);
	struct Process *processes=malloc(length*sizeof(struct Process));
	for (int i=0; i<length; i++)
	{
		processes[i].pid=i+1;
		printf("Enter the arrival time and burst time for process %d: ", i + 1);
		scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
	}
	FCFS(processes, length);
	SJF(processes, length);
	return 0;
}
