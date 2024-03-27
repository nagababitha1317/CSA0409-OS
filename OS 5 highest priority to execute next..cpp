#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int execution_time;
    int priority;
} Process;

void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void sort(Process *processes, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

void execute(Process *processes, int n) {
    printf("Execution order: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", processes[i].process_id);
    }
    printf("\n");

    printf("Process Execution:\n");
    for (int i = 0; i < n; i++) {
        printf("Executing P%d for %d units with priority %d\n", processes[i].process_id, processes[i].execution_time, processes[i].priority);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process *processes = (Process *) malloc(n * sizeof(Process));

    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter arrival time for P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter execution time for P%d: ", i + 1);
        scanf("%d", &processes[i].execution_time);
        printf("Enter priority for P%d (lower number indicates higher priority): ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    sort(processes, n);
    execute(processes, n);

    free(processes);

    return 0;
}

