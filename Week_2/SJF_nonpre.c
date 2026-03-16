// SJF -- > non preemptive... selects the one that is the shortest jon frist --> shortest burst time 
// WT --> since jobs finish faster thus the avg WT is low 
// RULE : Once a process starts, it cannot be stopped until it is finished, even if a shorter job arrives 
//halfway through.
// The "easy" trick here is to use a simple Bubble Sort to arrange the processes by Burst Time before 
//calculating.

#include<stdio.h>
int main() {
    int n, i, j, temp, bt[10], p[10], wt[10], tat[10];
    float awt=0, atat=0;
    // p stores the positions coz we need indexed positions to do the bubble sort

    printf("Enter number of processes: ");
    scanf("%d", &n);
    for(i=0; i<n; i++) {
        p[i] = i+1; // Store process number // its i+1 due to 1 based indexing
        printf("P%d burst time: ", i+1); // added process number.. now for the process number we have to add the bubble times
        scanf("%d", &bt[i]);
    }

    // Simple Bubble Sort to sort by Burst Time
    for(i=0; i<n; i++)
        for(j=i+1; j<n; j++) // j starts from the next one to i.
            if(bt[i] > bt[j]) { // if prev process is larger move it to end by sorting thus the shortest bt ones are earlier
                temp=bt[i]; bt[i]=bt[j]; bt[j]=temp;
                temp=p[i]; p[i]=p[j]; p[j]=temp;
            }
// rest is same as FCFS
    wt[0] = 0;
    for(i=1; i<n; i++) wt[i] = wt[i-1] + bt[i-1];

   printf("Process   BT    WT      TAT\n");
    for(i=0; i<n; i++) {
        tat[i] = bt[i] + wt[i];
        awt += wt[i]; atat += tat[i];
        printf("P%d\t %d\t %d\t %d\n", p[i], bt[i], wt[i], tat[i]);
    }
    printf("Avg WT: %.2f\nAvg TAT: %.2f", awt/n, atat/n);
    return 0;
}