#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100  // Maximum number of records in the file
#define BLOCK_SIZE 10    // Size of each block

typedef struct {
    int index_block[MAX_RECORDS];  // Index block containing pointers to file blocks
    int num_records;               // Number of records in the file
} File;

void allocate(File *file) {
    printf("Enter the number of records: ");
    scanf("%d", &file->num_records);

    if (file->num_records > MAX_RECORDS) {
        printf("Maximum number of records exceeded!\n");
        exit(1);
    }

    printf("Enter the index block pointers:\n");
    for (int i = 0; i < file->num_records; i++) {
        scanf("%d", &file->index_block[i]);
    }
}

void access_record(File *file, int record_number) {
    if (record_number < 1 || record_number > file->num_records) {
        printf("Invalid record number!\n");
        return;
    }

    int block_number = file->index_block[record_number - 1];
    int start_position = (block_number - 1) * BLOCK_SIZE;
    int end_position = start_position + BLOCK_SIZE - 1;

    printf("Accessing Record %d: Block Number = %d, Start Position = %d, End Position = %d\n", 
           record_number, block_number, start_position, end_position);
}

int main() {
    File file;
    int choice, record_number;

    allocate(&file);

    do {
        printf("\nMenu:\n");
        printf("1. Access a Record\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the record number to access: ");
                scanf("%d", &record_number);
                access_record(&file, record_number);
                break;
            case 2:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 2);

    return 0;
}

