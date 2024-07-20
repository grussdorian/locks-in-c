#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep()
#include <time.h> // For time()
#include "include/mcs_lock.h"

#define NUM_THREADS 4

mcs_lock_t lock;
qnode_t nodes[NUM_THREADS];
time_t start_time; // Global variable to hold the start time

// Thread function to test the MCS lock
void* thread_func(void* arg) {
    long id = (long)arg;
    qnode_t* node = &nodes[id];
    time_t current_time;

    current_time = time(NULL) - start_time; // Calculate the current time relative to the start time
    printf("[%ld seconds] Thread %ld attempting to acquire lock...\n", current_time, id);
    mcs_lock_test(&lock, node);
    current_time = time(NULL) - start_time;
    printf("[%ld seconds] Thread %ld has acquired the lock.\n", current_time, id);

    // Critical section
    current_time = time(NULL) - start_time;
    printf("[%ld seconds] Thread %ld is in the critical section.\n", current_time, id);

    // Sleep for a random time between 1 and 5 seconds
    unsigned int sleepTime = rand() % 5 + 1;
    current_time = time(NULL) - start_time;
    printf("[%ld seconds] Thread %ld sleeping for %u seconds...\n", current_time, id, sleepTime);
    sleep(sleepTime);

    mcs_unlock_test(&lock, node);
    current_time = time(NULL) - start_time;
    printf("[%ld seconds] Thread %ld has released the lock.\n", current_time, id);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize the MCS lock
    init_mcs_lock_test(&lock);

    // Seed the random number generator
    srand(time(NULL));

    // Record the start time
    start_time = time(NULL);

    // Create threads
    for (long i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, thread_func, (void*)i) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    time_t current_time = time(NULL) - start_time;
    printf("[%ld seconds] All threads have finished.\n", current_time);

    return 0;
}