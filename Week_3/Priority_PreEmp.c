// If a new process arrives with a higher priority than the one currently running, the CPU "swaps" them immediately. 
//This is also known as Preemptive Priority Scheduling.
/*
Imagine three tasks:
P1: Priority 2 (Low), Burst 5ms
P2: Priority 1 (High), Burst 3ms
In Non-Preemptive, if P1 starts first, P2 has to wait. In Preemptive, as soon as P2 arrives,
 P1 is paused so P2 can finish.
*/

#include<stdio.h>

int main() {
    int arrival[10], burst[10], priority[10], temp_burst[10];
    int i, count = 0, time = 0, n, smallest;
    double total_wait = 0, total_turn = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("P%d - Arrival, Burst, Priority: ", i + 1);
        scanf("%d %d %d", &arrival[i], &burst[i], &priority[i]);
        temp_burst[i] = burst[i]; // Store original burst for TAT/WT calc
    }

    // Set a dummy high-priority value for comparison (high number = low priority)
    priority[9] = 9999; 
    burst[9] = 9999;

    printf("\nProcess Execution Sequence:\n");

    for(time = 0; count != n; time++) {
        smallest = 9; // Reset to dummy index

        for(i = 0; i < n; i++) {
            // Check if process has arrived and has higher priority than current selection
            if(arrival[i] <= time && priority[i] < priority[smallest] && burst[i] > 0) {
                smallest = i;
            }
        }

        burst[smallest]--; // Execute the highest priority process for 1 unit

        // If process finishes
        if(burst[smallest] == 0) {
            count++;
            int completion_time = time + 1;
            total_wait += (completion_time - arrival[smallest] - temp_burst[smallest]);
            total_turn += (completion_time - arrival[smallest]);
        }
    }

    printf("\n\nAvg WT: %.2f", total_wait / n);
    printf("\nAvg TAT: %.2f\n", total_turn / n);

    return 0;
}