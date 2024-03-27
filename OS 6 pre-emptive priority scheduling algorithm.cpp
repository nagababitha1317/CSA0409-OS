#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int start_time;
    int end_time;
    int executed;
} Process;

int findHighestPriority(Process *processes, int n, int current_time) {
    int highest_priority = 9999;
    int highest_priority_index = -1;
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].executed == 0 && processes[i].priority < highest_priority) {
            highest_priority = processes[i].priority;
            highest_priority_index = i;
        }
    }
    return highest_priority_index;
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
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for P%d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].executed = 0;
    }

    int current_time = 0;
    int completed = 0;

    printf("\nExecution order:\n");
    while (completed < n) {
        int highest_priority_index = findHighestPriority(processes, n, current_time);

        if (highest_priority_index != -1) {
            processes[highest_priority_index].remaining_time--;

            printf("P%d ", processes[highest_priority_index].process_id);

            if (processes[highest_priority_index].remaining_time == 0) {
                completed++;
                processes[highest_priority_index].end_time = current_time + 1;
                processes[highest_priority_index].executed = 1;
            }
        } else {
            printf("Idle ");
        }

        current_time++;
    }

    printf("\n\nProcess Execution Details:\n");
    printf("PID\tArrival Time\tBurst Time\tPriority\tStart Time\tEnd Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].priority, processes[i].start_time, processes[i].end_time);
    }

    free(processes);

    return 0;
}

