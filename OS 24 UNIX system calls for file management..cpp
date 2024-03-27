#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void createFile(char *filename) {
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);

    if (fd == -1) {
        perror("Error creating file");
        exit(1);
    }

    printf("File created successfully: %s\n", filename);
    close(fd);
}

void writeFile(char *filename, char *data) {
    int fd = open(filename, O_WRONLY | O_APPEND);

    if (fd == -1) {
        perror("Error opening file for writing");
        exit(1);
    }

    if (write(fd, data, strlen(data)) == -1) {
        perror("Error writing to file");
        exit(1);
    }

    printf("Data written to file successfully.\n");
    close(fd);
}

void readFile(char *filename) {
    int fd = open(filename, O_RDONLY);
    char buffer[1024];

    if (fd == -1) {
        perror("Error opening file for reading");
        exit(1);
    }

    int bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead == -1) {
        perror("Error reading from file");
        exit(1);
    }

    buffer[bytesRead] = '\0';  // Null-terminate the string
    printf("Data read from file: %s\n", buffer);
    close(fd);
}

void modifyFile(char *filename, char *newData) {
    int fd = open(filename, O_WRONLY | O_TRUNC);

    if (fd == -1) {
        perror("Error opening file for modification");
        exit(1);
    }

    if (write(fd, newData, strlen(newData)) == -1) {
        perror("Error writing to file");
        exit(1);
    }

    printf("File modified successfully.\n");
    close(fd);
}

void deleteFile(char *filename) {
    if (unlink(filename) == -1) {
        perror("Error deleting file");
        exit(1);
    }

    printf("File deleted successfully: %s\n", filename);
}

int main() {
    char filename[] = "example.txt";
    char data[] = "Hello, this is a test file.\n";
    char newData[] = "This is modified data.\n";

    createFile(filename);
    writeFile(filename, data);
    readFile(filename);
    modifyFile(filename, newData);
    readFile(filename);
    deleteFile(filename);

    return 0;
}

