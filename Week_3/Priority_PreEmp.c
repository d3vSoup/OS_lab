// If a new process arrives with a higher priority than the one currently running, the CPU "swaps" them immediately. 
//This is also known as Preemptive Priority Scheduling.
/*
Imagine three tasks:
P1: Priority 2 (Low), Burst 5ms
P2: Priority 1 (High), Burst 3ms
In Non-Preemptive, if P1 starts first, P2 has to wait. In Preemptive, as soon as P2 arrives,
 P1 is paused so P2 can finish.
*/

#include <stdio.h>

struct Process {
    int pid;      // Process ID
    int bt;       // Burst Time
    int art;      // Arrival Time
    int pri;      // Priority
    int remaining_bt; 
};

int main() {
    int n, i, t = 0, completed = 0, shortest = 0;
    int min_pri = 9999; // Represents infinity
    float total_wt = 0, total_tat = 0;
    int finish_time;
    struct Process p[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("P[%d] Arrival, Burst, Priority: ", i + 1);
        scanf("%d %d %d", &p[i].art, &p[i].bt, &p[i].pri);
        p[i].remaining_bt = p[i].bt;
    }

    while (completed != n) {
        shortest = -1;
        min_pri = 9999;

        // Find process with highest priority available at current time 't'
        for (i = 0; i < n; i++) {
            if (p[i].art <= t && p[i].remaining_bt > 0 && p[i].pri < min_pri) {
                min_pri = p[i].pri;
                shortest = i;
            }
        }

        if (shortest == -1) {
            t++;
            continue;
        }

        // Execute for 1 unit of time
        p[shortest].remaining_bt--;

        // If a process is finished
        if (p[shortest].remaining_bt == 0) {
            completed++;
            finish_time = t + 1;
            int wt = finish_time - p[shortest].bt - p[shortest].art;
            if (wt < 0) wt = 0;
            
            total_wt += wt;
            total_tat += (finish_time - p[shortest].art);
            
            printf("\nP[%d] finished at time %d | WT: %d | TAT: %d", 
                   p[shortest].pid, finish_time, wt, finish_time - p[shortest].art);
        }
        t++;
    }

    printf("\n\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}