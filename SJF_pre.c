/*
Think of Preemptive SJF (SRTF) like a doctor’s office that handles emergencies. If a doctor is 
treating a patient with a minor cold (Long Burst Time) and someone walks in with a broken
 arm (Short Burst Time), the doctor stops treating the cold and immediately starts on the broken arm


In FCFS, a process waits once, then runs until it's done. 
In Preemptive SJF, a process might start, get kicked out, wait again, and start again later.

Because of this "stop-and-start" nature, we use a simple subtraction formula to
 find the total time it spent just sitting there:


 WT = \text{Total Time in System (TAT)} - \text{Actual Work Time (BT)}

 Imagine these two processes:

P1: Arrives at 0, Burst = 8
P2: Arrives at 1, Burst = 4

At Time 0: Only P1 is here. It starts running.
At Time 1: P2 arrives.
P1 has 7ms remaining.
P2 only needs 4ms.
P2 is shorter! The CPU kicks P1 out and starts P2.
At Time 5: P2 finishes. Now the CPU goes back to the remaining 7ms of P1.


*/





#include<stdio.h>
int main() {
    int a[10], b[10], temp[10], i, smallest, count=0, time, n;
    double wait=0, turn=0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    for(i=0; i<n; i++) {
        printf("Arrival & Burst for P%d: ", i+1); // 1 based indexing
        // arrival and burst times 
        scanf("%d%d", &a[i], &b[i]);
        temp[i] = b[i]; // Store original burst times in a temp array
    }
    // shorter arrAY TO STORE remaining time
    b[9] = 9999; // Placeholder for comparison
    for(time=0; count!=n; time++) {
        smallest = 9;0
        for(i=0; i<n; i++) {
            if(a[i] <= time && b[i] < b[smallest] && b[i] > 0)
                smallest = i;
        }
        b[smallest]--; // Reduce remaining time
        if(b[smallest] == 0) {
            count++;
            wait += time + 1 - a[smallest] - temp[smallest];
            turn += time + 1 - a[smallest];
        }
    }
    printf("Avg WT: %.2f\nAvg TAT: %.2f", wait/n, turn/n);
    return 0;
}