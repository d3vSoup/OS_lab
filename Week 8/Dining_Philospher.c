/* =============================================================================
dining philosophers
1. The Problem: 5 philosophers sit at a table with 5 forks. A philosopher 
   needs 2 forks (left and right) to eat. If everyone grabs their left fork 
   at the exact same time, no one can get a right fork. That's a Deadlock.
2. The Setup: We use `pthread_mutex_t` to represent the forks. A mutex acts 
   like a lock—if a philosopher locks a fork, no one else can use it.
3. The Solution (Deadlock Avoidance): The easiest way to prevent deadlock 
   is to break the symmetry. We make the last philosopher (Philosopher 4) 
   pick up their RIGHT fork first, then their LEFT. Everyone else picks up 
   LEFT, then RIGHT. This guarantees at least one person can always eat!
4. The Flow: They Think -> Grab Forks -> Eat (sleep for 1 sec) -> Drop Forks.
=============================================================================
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define N 5
pthread_mutex_t forks[N];
void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;            
    int right = (id + 1) % N;
    printf("Philosopher %d is thinking...\n", id);
    if (id == N - 1) {
        pthread_mutex_lock(&forks[right]);
        pthread_mutex_lock(&forks[left]);
    } else {
        pthread_mutex_lock(&forks[left]);
        pthread_mutex_lock(&forks[right]);
    }
    printf("Philosopher %d is eating!\n", id);
    sleep(1);
    pthread_mutex_unlock(&forks[left]);
    pthread_mutex_unlock(&forks[right]);
    printf("Philosopher %d finished eating.\n", id);
    return NULL;    
}

int main() {
    pthread_t threads[N];
    int ids[N];
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);

    }
}