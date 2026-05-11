#include<stdio.h>

#define MAX 10

typedef struct {
    int id;
    int execution_time;
    int period;
    int remaining_time;
    int next_arrival;
} Task;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    Task tasks[MAX];
    int n, hyperperiod=1;

    printf("Enter number of tasks:");
    scanf("%d", &n);

    for(int i=0;i<n;i++){
        printf("\nTask %d\n", i+1);
        tasks[i].id=i+1;

        printf("Execution Time:");
        scanf("%d", &tasks[i].execution_time);

        printf("Period:");
        scanf("%d", &tasks[i].period);

        tasks[i].remaining_time=0;
        tasks[i].next_arrival=0;

        if(i==0) hyperperiod = tasks[i].period;
        else hyperperiod = lcm(hyperperiod, tasks[i].period);
    }

    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(tasks[i].period>tasks[j].period){
                Task temp=tasks[i];
                tasks[i]=tasks[j];
                tasks[j]=temp;
            }
        }
    }

    printf("\nGantt Chart\n");

for(int time=0; time<hyperperiod; time++){
    for(int i=0; i<n; i++){
        if(time == tasks[i].next_arrival){
            tasks[i].remaining_time = tasks[i].execution_time;
            tasks[i].next_arrival += tasks[i].period;
        }
    }
    int executed = -1;

    for(int i=0; i<n; i++){
        if(tasks[i].remaining_time > 0){
            executed = i;
            break;
        }
    }

    if(executed != -1){
        printf("| T%d  ", tasks[executed].id);
        tasks[executed].remaining_time--;
    } else {
        printf("| Idle ");
    }
}
printf("|\n");


for(int i=0; i<=hyperperiod; i++){
    printf("%5d", i);
}
printf("\n");
    printf("0");
    for(int i=1;i<=hyperperiod;i++){
        printf(" %d", i);
    }

    printf("\n");
    return 0;
}
