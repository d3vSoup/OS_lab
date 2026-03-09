// This is the fair algo
// Every process gets a small, fixed unit of time called a Time Quantum (or Time Slice). 
//If the process isn't finished when its time is up, it goes to the back of the line.

/*
Imagine a round-robin tournament where each player gets a turn to play for a short time. 
If a player isn't done when their turn ends, they go to the back of the line and wait for their next turn.

The ExampleProcesses: P1 (Burst 10ms), P2 (Burst 4ms)
Time Quantum: 3ms
The flow:
P1 runs for 3ms 
    P2 runs for 3ms 
        P1 runs for 3ms 
            P2 runs for 1ms (finished) 
                P1 finishes the rest.
*/

#include <stdio.h>

int main() {
    int i, n, sum = 0, count = 0, y, quant, wt = 0, tat = 0, bt[10], temp[10];
    float avg_wt, avg_tat;

    printf("Total number of processes: ");
    scanf("%d", &n);
    y = n; 

    for(i = 0; i < n; i++) {
        printf("Enter Burst Time for P[%d]: ", i + 1);
        scanf("%d", &bt[i]);
        temp[i] = bt[i]; // Store burst time in temp array
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quant);

    printf("\nProcess No \tBurst Time \tTAT \tWaiting Time");
    for(sum = 0, i = 0; y != 0; ) {
        if(temp[i] <= quant && temp[i] > 0) {
            sum = sum + temp[i];
            temp[i] = 0;
            count = 1;
        } else if(temp[i] > 0) {
            temp[i] = temp[i] - quant;
            sum = sum + quant;
        }

        if(temp[i] == 0 && count == 1) {
            y--; // One process finished
            printf("\nP[%d] \t\t %d \t\t %d \t\t %d", i + 1, bt[i], sum, sum - bt[i]);
            wt = wt + (sum - bt[i]);
            tat = tat + sum;
            count = 0;
        }

        if(i == n - 1) i = 0;
        else i++;
    }

    avg_wt = wt * 1.0 / n;
    avg_tat = tat * 1.0 / n;
    printf("\n\nAverage Waiting Time: %.2f", avg_wt);
    printf("\nAverage Turnaround Time: %.2f", avg_tat);
}
