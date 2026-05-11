#include<stdio.h>

struct process
{
    int id;
    int busrt_time;
    int deadline;
};

int main()
{
    int n,i,j;
    struct process p[10],temp;

    printf("Enter number of processes:");
    scanf("%d", &n);

    for(i=0;i<n;i++){
        printf("\n Process %d:\n", i+1);
        p[i].id=i+1;
        printf("Burst Time:");
        scanf("%d", &p[i].busrt_time);
        printf("Deadline:");
        scanf("%d", &p[i].deadline);
    }

    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(p[j].deadline>p[j+1].deadline){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }

    printf("\n Execution Order(EOF):\n");
    for(i=0;i<n;i++){
        printf("P%d", p[i].id);
    }

    return 0;
}
