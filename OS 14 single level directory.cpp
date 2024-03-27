#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to create a new file
void createFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating file %s\n", filename);
        exit(1);
    }
    printf("File %s created successfully.\n", filename);
    fclose(file);
}

// Function to list all files in a directory
void listFiles() {
    system("ls");
}

// Function to delete a file
void deleteFile(const char *filename) {
    if (remove(filename) == 0) {
        printf("File %s deleted successfully.\n", filename);
    } else {
        printf("Error deleting file %s\n", filename);
    }
}

int main() {
    int choice;
    char filename[50];

    while (1) {
        printf("\nSingle Level Directory Operations\n");
        printf("1. Create File\n");
        printf("2. List Files\n");
        printf("3. Delete File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter filename to create: ");
                scanf("%s", filename);
                createFile(filename);
                break;
            case 2:
                printf("Files in directory:\n");
                listFiles();
                break;
            case 3:
                printf("Enter filename to delete: ");
                scanf("%s", filename);
                deleteFile(filename);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}

