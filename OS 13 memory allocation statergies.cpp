#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 100

typedef struct {
    int size;
    int allocated;
} Block;

Block memory[MEMORY_SIZE];

void initialize_memory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i].size = 0;
        memory[i].allocated = 0;
    }
}

void display_memory() {
    printf("Memory Status:\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].allocated) {
            printf("Block %d: Allocated, Size = %d\n", i, memory[i].size);
        } else {
            printf("Block %d: Free, Size = %d\n", i, memory[i].size);
        }
    }
    printf("\n");
}

// First Fit
int first_fit(int size) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (!memory[i].allocated && memory[i].size >= size) {
            memory[i].allocated = 1;
            return i;
        }
    }
    return -1;
}

// Best Fit
int best_fit(int size) {
    int best_fit_index = -1;
    int min_size = MEMORY_SIZE + 1;
    
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (!memory[i].allocated && memory[i].size >= size && memory[i].size < min_size) {
            best_fit_index = i;
            min_size = memory[i].size;
        }
    }
    
    if (best_fit_index != -1) {
        memory[best_fit_index].allocated = 1;
    }
    
    return best_fit_index;
}

// Worst Fit
int worst_fit(int size) {
    int worst_fit_index = -1;
    int max_size = -1;
    
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (!memory[i].allocated && memory[i].size >= size && memory[i].size > max_size) {
            worst_fit_index = i;
            max_size = memory[i].size;
        }
    }
    
    if (worst_fit_index != -1) {
        memory[worst_fit_index].allocated = 1;
    }
    
    return worst_fit_index;
}

// Next Fit
int next_fit(int size, int last_allocated) {
    for (int i = (last_allocated + 1) % MEMORY_SIZE; i != last_allocated; i = (i + 1) % MEMORY_SIZE) {
        if (!memory[i].allocated && memory[i].size >= size) {
            memory[i].allocated = 1;
            return i;
        }
    }
    return -1;
}

int main() {
    initialize_memory();

    // Set initial memory blocks
    memory[0].size = 20;
    memory[1].size = 30;
    memory[2].size = 10;
    memory[3].size = 40;

    while (1) {
        int choice, size, index;
        printf("Select Memory Allocation Strategy:\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Next Fit\n");
        printf("5. Display Memory\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter size to allocate: ");
                scanf("%d", &size);
                index = first_fit(size);
                if (index == -1) {
                    printf("Memory allocation failed\n");
                } else {
                    printf("Memory allocated at Block %d\n", index);
                }
                break;
            case 2:
                printf("Enter size to allocate: ");
                scanf("%d", &size);
                index = best_fit(size);
                if (index == -1) {
                    printf("Memory allocation failed\n");
                } else {
                    printf("Memory allocated at Block %d\n", index);
                }
                break;
            case 3:
                printf("Enter size to allocate: ");
                scanf("%d", &size);
                index = worst_fit(size);
                if (index == -1) {
                    printf("Memory allocation failed\n");
                } else {
                    printf("Memory allocated at Block %d\n", index);
                }
                break;
            case 4:
                printf("Enter size to allocate: ");
                scanf("%d", &size);
                printf("Enter last allocated block index: ");
                int last_allocated;
                scanf("%d", &last_allocated);
                index = next_fit(size, last_allocated);
                if (index == -1) {
                    printf("Memory allocation failed\n");
                } else {
                    printf("Memory allocated at Block %d\n", index);
                }
                break;
            case 5:
                display_memory();
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}

