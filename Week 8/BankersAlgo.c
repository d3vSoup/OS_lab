/* =============================================================================
HOW THIS CODE WORKS (BANKER'S ALGORITHM):
1. The Concept: Think of the OS as a bank. It won't loan out money (resources) 
   unless it's absolutely sure it can get it back. It checks if granting a 
   request leaves the system in a "Safe State".
2. The Matrices: 
   - alloc[][]: What each process currently holds.
   - max[][]: The maximum resources each process will ever need.
   - avail[]: What the system currently has sitting free.
   - need[][]: What they still need (Calculated as: max - alloc).
3. The Logic: 
   - The code scans for a process whose `need` is less than or equal to `avail`.
   - If it finds one, it assumes that process finishes, takes back its 
     allocated resources, and adds them to `avail`.
   - It marks the process as finished (`f[i] = 1`) and adds it to the safe sequence.
4. The Result: If it can line up all processes to finish without running out 
   of resources, it prints the "Safe Sequence".
=============================================================================
*/

#include <stdio.h>
int main() {
    int n = 5,m = 3;
    int alloc[5][3] = { {0, 1, 0},   {2, 0, 0},   {3, 0, 2},       {2, 1, 1},  {0, 0, 2} }; 
    int max[5][3] =   { {7, 5, 3},     {3, 2, 2},    {9, 0, 2},    {2, 2, 2},    {4, 3, 3} }; 
    int avail[3] = {3, 3, 2};
    int f[5] = {0}; 
    int ans[5], ind = 0;
    int need[5][3];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    for (int k = 0; k < 5; k++) {
        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]){ 
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1; 
                }
            }
        }
    }
    printf("Safe Sequence is: \n");
    for (int i = 0; i < n - 1; i++) {
        printf(" P%d ->", ans[i]);
    }
    printf(" P%d\n", ans[n - 1]);
}