clude <stdio.h>

struct process {
    int id;
    int burst_time;
    int weight;
};

int main() {
    int n, i, total_weight = 0, time_quantum = 100;
    struct process p[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);
        p[i].id = i + 1;

        printf("Burst Time: ");
        scanf("%d", &p[i].burst_time);

        printf("Weight (Priority Share): ");
        scanf("%d", &p[i].weight);

        total_weight += p[i].weight;
    }

    printf("\nProportional Scheduling:\n");
    for (i = 0; i < n; i++) {
        float cpu_share = ((float)p[i].weight / total_weight) * time_quantum;
        printf("P%d -> Burst Time=%d, CPU share=%.2f units\n", p[i].id, p[i].burst_time, cpu_share);
    }

    return 0;
}
