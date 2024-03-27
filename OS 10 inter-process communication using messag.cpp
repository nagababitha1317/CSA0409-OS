#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 128  // Maximum size of the message
#define MSG_TYPE 1    // Message type

typedef struct {
    long msg_type;
    char msg_text[MSG_SIZE];
} Message;

int main() {
    int msgid;
    key_t key = 1234;  // Key to identify the message queue
    Message message;

    // Create a message queue
    if ((msgid = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        exit(1);
    }

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        // Parent process
        
        printf("Parent process sending message to the queue...\n");
        message.msg_type = MSG_TYPE;
        strncpy(message.msg_text, "Hello from parent process!", MSG_SIZE);

        // Send the message to the queue
        if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        // Wait for the child process to receive the message
        sleep(2);
    } else {
        // Child process

        // Receive the message from the queue
        if (msgrcv(msgid, &message, sizeof(message.msg_text), MSG_TYPE, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Child process received message from the queue: %s\n", message.msg_text);
        
        // Modify and send the message back to the queue
        strncpy(message.msg_text, "Hello from child process!", MSG_SIZE);

        // Send the modified message to the queue
        if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
    }

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}

