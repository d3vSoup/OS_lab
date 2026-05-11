#include <stdio.h>

int main() {
    int n = 5;
    int m = 3;

    int alloc[5][3] = { 
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    }; 

    int request[5][3] = { 
        {0, 0, 0},
        {2, 0, 2},
        {0, 0, 0},
        {1, 0, 0},
        {0, 0, 2}
    }; 

    int avail[3] = {0, 0, 0}; 

    int f[5] = {0};
    int ans[5], ind = 0;

    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                int can_be_allocated = 1;
                
                for (int j = 0; j < m; j++) {
                    if (request[i][j] > avail[j]) { 
                        can_be_allocated = 0;
                        break;
                    }
                }
                
                if (can_be_allocated == 1) {
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    int is_deadlock = 0;
    printf("Deadlock Detection Results:\n");
    printf("---------------------------\n");
    
    for (int i = 0; i < n; i++) {
        if (f[i] == 0) {
            is_deadlock = 1;
            printf("Process P%d is DEADLOCKED.\n", i);
        }
    }

    if (is_deadlock == 0) {
        printf("System is NOT in deadlock.\n");
        printf("Execution Sequence: ");
        for (int i = 0; i < n - 1; i++) {
            printf("P%d -> ", ans[i]);
        }
        printf("P%d\n", ans[n - 1]);
    } else {
        printf("\nThe system is currently in a DEADLOCK state.\n");
    }

    return 0;
}