#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define EAT_COUNT 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    for (int i = 0; i < EAT_COUNT; i++) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);  // Thinking
        printf("Philosopher %d wants to eat\n", id);

        pthread_mutex_lock(&forks[left]);
        printf("Philosopher %d picked up left fork %d\n", id, left);
        
        // Yield to give other philosophers a chance to pick up their left forks
        usleep(1000);

        if (pthread_mutex_trylock(&forks[right]) != 0) {
            printf("Philosopher %d couldn't pick up right fork %d\n", id, right);
            pthread_mutex_unlock(&forks[left]);
            continue;
        }

        printf("Philosopher %d picked up right fork %d and is eating\n", id, right);
        
        sleep(2);  // Eating

        printf("Philosopher %d put down right fork %d\n", id, right);
        pthread_mutex_unlock(&forks[right]);
        
        printf("Philosopher %d put down left fork %d\n", id, left);
        pthread_mutex_unlock(&forks[left]);
    }

    printf("Philosopher %d finished eating\n", id);
    return NULL;
}

int main() {
    int ids[NUM_PHILOSOPHERS];

    // Initialize mutex locks for each fork
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_mutex_init(&forks[i], NULL) != 0) {
            perror("Mutex initialization failed");
            exit(1);
        }
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopher, &ids[i]) != 0) {
            perror("Thread creation failed");
            exit(1);
        }
    }

    // Wait for philosopher threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutex locks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

