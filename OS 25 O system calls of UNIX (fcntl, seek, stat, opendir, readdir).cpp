#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

// Function to demonstrate fcntl system call
void demonstrate_fcntl(int fd) 
{
    int flags;

    flags = fcntl(fd,F_GETFL);

    if (flags == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }

    printf("File descriptor flags: %d\n", flags);
}

// Function to demonstrate lseek system call
void demonstrate_lseek(int fd) {
    off_t offset;

    offset = lseek(fd, 0, SEEK_END);

    if (offset == -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    printf("File size: %lld bytes\n", (long long)offset);
}

// Function to demonstrate stat system call
void demonstrate_stat(const char *path) {
    struct stat file_stat;

    if (stat(path, &file_stat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("File information for %s:\n", path);
    printf("File size: %lld bytes\n", (long long)file_stat.st_size);
    printf("File permissions: %o\n", file_stat.st_mode & 0777);
}

// Function to demonstrate opendir and readdir system calls
void demonstrate_opendir(const char *path) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(path);

    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    printf("Contents of directory %s:\n", path);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

int main() {
    int fd;
    const char *file_path = "test.txt";
    const char *dir_path = ".";

    // Open a file
    fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Demonstrate fcntl
    printf("Demonstrating fcntl:\n");
    demonstrate_fcntl(fd);

    // Demonstrate lseek
    printf("\nDemonstrating lseek:\n");
    demonstrate_lseek(fd);

    // Close the file
    close(fd);

    // Demonstrate stat
    printf("\nDemonstrating stat:\n");
    demonstrate_stat(file_path);

    // Demonstrate opendir and readdir
    printf("\nDemonstrating opendir and readdir:\n");
    demonstrate_opendir(dir_path);

    return 0;
}

