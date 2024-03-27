#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 10

// Shared data between producer and consumer
int buffer[BUFFER_SIZE];
int count = 0;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int i;
    for (i = 0; i < 20; i++) {
        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) {
            printf("Buffer is full. Producer waits.\n");
            pthread_mutex_unlock(&mutex);
            sleep(1);  // Sleep for 1 second
            pthread_mutex_lock(&mutex);
        }

        buffer[count] = i;
        printf("Produced: %d\n", buffer[count]);
        count++;

        pthread_mutex_unlock(&mutex);
        sleep(1);  // Sleep for 1 second
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < 20; i++) {
        pthread_mutex_lock(&mutex);

        while (count == 0) {
            printf("Buffer is empty. Consumer waits.\n");
            pthread_mutex_unlock(&mutex);
            sleep(1);  // Sleep for 1 second
            pthread_mutex_lock(&mutex);
        }

        count--;
        printf("Consumed: %d\n", buffer[count]);

        pthread_mutex_unlock(&mutex);
        sleep(1);  // Sleep for 1 second
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producerThread, consumerThread;

    // Initialize mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Mutex initialization failed.\n");
        return 1;
    }

    // Create producer and consumer threads
    if (pthread_create(&producerThread, NULL, producer, NULL) != 0) {
        printf("Producer thread creation failed.\n");
        return 1;
    }

    if (pthread_create(&consumerThread, NULL, consumer, NULL) != 0) {
        printf("Consumer thread creation failed.\n");
        return 1;
    }

    // Wait for threads to finish
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

