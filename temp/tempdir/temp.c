#include "CSC718/pthread/pthread/pthread_barrier_compat.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_THREADS 3
pthread_barrier_t barrier;

void *worker(void *arg) {
    int id = *(int *)arg;
    
    printf("Thread %d: Starting work...\n", id);
    // sleep(id + 1);  // Simulate different work loads
    printf("Thread %d: Reached barrier\n", id);
    
    // Wait for all threads to reach this point
    pthread_barrier_wait(&barrier);
    
    printf("Thread %d: Passed barrier, continuing...\n", id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    // Initialize barrier for 3 threads
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, worker, &thread_ids[i]);
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    pthread_barrier_destroy(&barrier);
    printf("All threads finished\n");
    return 0;
}