#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function executed by each thread
void *print_message(void *ptr) {
    char *message = (char *)ptr;
    printf("%s\n", message);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    char *message1 = "Thread 1 is running";
    char *message2 = "Thread 2 is running";

    // Create thread 1
    if (pthread_create(&thread1, NULL, print_message, (void *)message1) != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    // Create thread 2
    if (pthread_create(&thread2, NULL, print_message, (void *)message2) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Both threads have finished executing\n");

    return 0;
}
