// FCFS -> stands for First Come First serve 
// So its like first in First out 

/*

In every scheduling program, we use these two standard equations:
Turnaround Time (TAT): The total time from when a process arrives until it finishes.
TAT = \text{Completion Time} - \text{Arrival Time}

Waiting Time (WT): The total time a process spends sitting in the queue.
WT = TAT - \text{Burst Time}

*/

// In FCFS -- > its a movie theatre line... whoever comes frist is served first
// Waiting time : A process waits for the sum of the burst times of all processes that came before it.
// Flaw : if a huge process comes b4 other small ones then it takes time to do that process before 
// moving to smaller ones.... This is called Convoy Effect 

#include<stdio.h>
int main() {
    int n, i, bt[10], wt[10], tat[10];
    // take separate arrays for burst time --> khudka time, wt--> waiting time, tat --> total time of processor till that process 

    float awt=0, atat=0; // calc avg wt and avg tat

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter burst times: ");
    for(i=0; i<n; i++) scanf("%d", &bt[i]); // burst times of all these processes. Burst time = indv process time 

    wt[0] = 0; // First process doesn't wait
    for(i=1; i<n; i++) wt[i] = wt[i-1] + bt[i-1]; // this is like a prefiux sum scenario of adding wt for next process = wt of process process + burst time of previous process 

    printf("Process   BT    WT      TAT\n");
    for(i=0; i<n; i++) {
        tat[i] = bt[i] + wt[i]; // tat of a process --> bt + wt of a process 
        awt += wt[i];
        atat += tat[i];
        printf("P%d\t %d\t %d\t %d\n", i+1, bt[i], wt[i], tat[i]);
    }
    printf("Avg WT: %.2f\nAvg TAT: %.2f", awt/n, atat/n);
    return 0;
}