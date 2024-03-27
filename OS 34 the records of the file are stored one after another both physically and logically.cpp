#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100  // Maximum number of records in the file

typedef struct {
    int start;      // Starting position of the record
    int length;     // Length of the record
} Record;

void allocate(Record records[], int num_records) {
    int current_position = 0;  // Current position in the file

    printf("Record\tStart\tLength\n");
    for (int i = 0; i < num_records; i++) {
        records[i].start = current_position;
        records[i].length = rand() % 10 + 1;  // Random length between 1 to 10
        current_position += records[i].length;

        printf("%d\t%d\t%d\n", i + 1, records[i].start, records[i].length);
    }
}

void access_record(Record records[], int num_records, int record_number) {
    if (record_number < 1 || record_number > num_records) {
        printf("Invalid record number!\n");
        return;
    }

    printf("Accessing Record %d: Start = %d, Length = %d\n", record_number, 
           records[record_number - 1].start, records[record_number - 1].length);
}

int main() {
    int num_records;
    Record records[MAX_RECORDS];

    printf("Enter the number of records: ");
    scanf("%d", &num_records);

    if (num_records > MAX_RECORDS) {
        printf("Maximum number of records exceeded!\n");
        return 1;
    }

    allocate(records, num_records);

    int choice, record_number;
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
                access_record(records, num_records, record_number);
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

