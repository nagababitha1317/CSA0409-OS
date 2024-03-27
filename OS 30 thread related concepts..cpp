#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message(void *ptr) {
    char *message = (char *) ptr;
    printf("%s\n", message);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    const char *message1 = "Thread 1";
    const char *message2 = "Thread 2";

    pthread_create(&thread1, NULL, print_message, (void *) message1);
    pthread_create(&thread2, NULL, print_message, (void *) message2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

