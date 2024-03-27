#include<stdio.h>

struct Process {
    int pid;            // Process ID
    int arrival_time;   // Arrival time
    int burst_time;     // Burst time
    int waiting_time;   // Waiting time
    int turnaround_time;// Turnaround time
};

void findWaitingTime(struct Process proc[], int n) {
    int wt[n];
    wt[0] = 0;

    // Calculate waiting time
    for (int i = 1; i < n; i++) {
        wt[i] = 0;
        for (int j = 0; j < i; j++)
            wt[i] += proc[j].burst_time;
    }

    // Assign waiting time
    for (int i = 0; i < n; i++) {
        proc[i].waiting_time = wt[i] - proc[i].arrival_time;
        if (proc[i].waiting_time < 0)
            proc[i].waiting_time = 0;
    }
}

void findTurnAroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++)
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
}

void findAverageTime(struct Process proc[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;

    findWaitingTime(proc, n);
    findTurnAroundTime(proc, n);

    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
    }

    printf("Average waiting time = %.2f\n", (float)total_waiting_time / (float)n);
    printf("Average turnaround time = %.2f\n", (float)total_turnaround_time / (float)n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process P%d: ", i + 1);
        scanf("%d%d", &proc[i].arrival_time, &proc[i].burst_time);
        proc[i].pid = i + 1;
    }

    findAverageTime(proc, n);

    return 0;
}

