/* =========================================================================
   MULTI-LEVEL QUEUE SCHEDULING (NON-PREEMPTIVE) WITH FCFS
   
   EXAMPLE SCENARIO:
   -------------------------------------------------------------------------
   Queue 1 = System Process (High Priority)
   Queue 2 = User Process (Low Priority)
   
   PID | Arrival Time (AT) | Burst Time (BT) | Queue Type (QT)
   -----------------------------------------------------------
   1   | 0                 | 5               | 2 (User)
   2   | 1                 | 3               | 1 (System)
   3   | 2                 | 4               | 1 (System)
   4   | 3                 | 2               | 2 (User)

   EXECUTION TIMELINE (GANTT CHART LOGIC):
   -------------------------------------------------------------------------
   Time 0 to 5 : P1 runs. It's a User process, but it's the ONLY one that 
                 has arrived at time 0. Since this is non-preemptive, it 
                 runs to completion.
   Time 5 to 8 : P1 is done. P2, P3, and P4 are now waiting. 
                 P2 and P3 are System processes (Queue 1), so they beat P4.
                 Between P2 and P3, P2 arrived first (FCFS). P2 runs.
   Time 8 to 12: P3 runs next because it's the remaining System process.
   Time 12 to 14: P4 runs last because it's a User process (Queue 2).

   EXPECTED OUTPUT:
   -------------------------------------------------------------------------
   Average Turnaround Time: 8.25
   Average Waiting Time: 4.75
   ========================================================================= */

#include <stdio.h>

int main() {
    int n, i;
    
    // Parallel arrays to store process data. Size 10 is used for simplicity.
    int pid[10]; // Process ID
    int at[10];  // Arrival Time
    int bt[10];  // Burst Time
    int qt[10];  // Queue Type (1 for System, 2 for User)
    int ct[10];  // Completion Time
    int tat[10]; // Turnaround Time
    int wt[10];  // Waiting Time
    
    // Array to keep track of which processes are finished. 0 = No, 1 = Yes.
    int done[10] = {0}; 

    int completed = 0;   // Counter for how many processes have finished
    int current_time = 0; // The CPU clock
    float total_tat = 0, total_wt = 0; // Trackers for calculating averages

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // 1. Collect process details from the user
    for(i = 0; i < n; i++) {
        pid[i] = i + 1; // Assign Process ID (1, 2, 3...)
        printf("\nProcess %d -> Arrival Time, Burst Time, Queue (1=System, 2=User): ", pid[i]);
        scanf("%d %d %d", &at[i], &bt[i], &qt[i]);
    }

    // 2. Scheduling Loop - Keeps running until all processes are done
    while (completed < n) {
        int selected = -1;           // Holds the index of the process we choose to run
        int best_queue = __INT_MAX__;        // Start with a dummy low priority to find the highest (1 is highest)
        int earliest_arrival = __INT_MAX__;  // Start with a dummy high arrival time to find the earliest

        // Loop through all processes to evaluate who is waiting and ready to run
        for(i = 0; i < n; i++) {
            
            // CONDITION 1: Has the process arrived? AND is it still incomplete?
            if (at[i] <= current_time && done[i] == 0) {
                
                // CONDITION 2 (Priority): Does it belong to a better (lower number) queue?
                // Example: If best_queue is currently 2, and we find a 1, the 1 takes over.
                if (qt[i] < best_queue) {
                    best_queue = qt[i];
                    earliest_arrival = at[i];
                    selected = i;
                } 
                // CONDITION 3 (FCFS): If the queue priority is exactly the same...
                // ...we use First-Come, First-Served based on arrival time.
                else if (qt[i] == best_queue) {
                    if (at[i] < earliest_arrival) {
                        earliest_arrival = at[i];
                        selected = i;
                    }
                }
            }
        }

        // 3. Execution Phase
        if (selected != -1) {
            // A process was selected! Since it's non-preemptive, we jump time forward 
            // by the entire burst time of the selected process.
            current_time = current_time + bt[selected]; 
            
            // Calculate when it finished and how long it had to wait
            ct[selected] = current_time;                      // Completion Time
            tat[selected] = ct[selected] - at[selected];      // Turnaround = Completion - Arrival
            wt[selected] = tat[selected] - bt[selected];      // Waiting = Turnaround - Burst
            
            done[selected] = 1; // Mark this process as successfully completed
            completed++;        // Increment our completion counter
            
            // Add to our running totals for the final averages
            total_tat += tat[selected];
            total_wt += wt[selected];
        } else {
            // CPU IDLE STATE: If we reach here, no processes have arrived by the 'current_time'.
            // We just tick the clock forward by 1 unit and check again.
            current_time++;
        }
    }

    // 4. Print the final results table
    //printf("\n-------------------------------------------------------------------------");
    printf("\nPID\tQueue\tArrival\tBurst\tComplete\tTurnaround\tWaiting\n");
    //printf("-------------------------------------------------------------------------\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\t\t%d\n", 
               pid[i], qt[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    
    // Print the mathematical averages
    //printf("-------------------------------------------------------------------------\n");
    printf("Avg Turnaround Time: %.2f\n", total_tat / n);
    printf("Avg Waiting Time: %.2f\n", total_wt / n);

}