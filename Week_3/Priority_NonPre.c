// Finishes BT execution regardless of if other process has higher priority or not. 
/*
Imagine three tasks:
P1: Priority 2 (Low), Burst 5ms
P2: Priority 1 (High), Burst 3ms
In Non-Preemptive, if P1 starts first, P2 has to wait. In Preemptive, as soon as P2 arrives,
 P1 is paused so P2 can finish.
*/

#include <stdio.h>

int main() {
    int bt[20], p[20], wt[20], tat[20], pr[20], i, j, n, total = 0, pos, temp;
    float avg_wt, avg_tat;

    printf("Enter Total Number of Processes: ");
    scanf("%d", &n);

    printf("\nEnter Burst Time and Priority\n");
    for(i = 0; i < n; i++) {
        printf("P[%d] Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
        printf("P[%d] Priority: ", i + 1);
        scanf("%d", &pr[i]);
        p[i] = i + 1;
    }
    for(i = 0; i < n; i++) {
        pos = i;
        for(j = i + 1; j < n; j++) {
            if(pr[j] < pr[pos]) pos = j;
        }
        temp = pr[i]; pr[i] = pr[pos]; pr[pos] = temp;
        temp = bt[i]; bt[i] = bt[pos]; bt[pos] = temp;
        temp = p[i]; p[i] = p[pos]; p[pos] = temp;
    }

    wt[0] = 0; 
    for(i = 1; i < n; i++) {
        wt[i] = 0;
        for(j = 0; j < i; j++) wt[i] += bt[j];
        total += wt[i];
    }

    avg_wt = (float)total / n;
    total = 0;
    printf("\nProcess\tBT\tPriority\tWT\tTAT");
    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total += tat[i];
        printf("\nP[%d]\t%d\t%d\t\t%d\t%d", p[i], bt[i], pr[i], wt[i], tat[i]);
    }
    avg_tat = (float)total / n;
    printf("\n\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);
}