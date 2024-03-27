#include<stdio.h>

struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
};

void calculateTimes(struct Process p[], int n) {
    int i;
    float total_wait = 0, total_turnaround = 0;

    // Waiting time for the first process is 0
    p[0].waiting = 0;
    
    // Calculate waiting time
    for(i = 1; i < n; i++) {
        p[i].waiting = p[i-1].waiting + p[i-1].burst;
    }

    // Calculate turnaround time
    for(i = 0; i < n; i++) {
        p[i].turnaround = p[i].waiting + p[i].burst;
    }

    // Calculate total waiting and turnaround time
    for(i = 0; i < n; i++) {
        total_wait += p[i].waiting;
        total_turnaround += p[i].turnaround;
    }

    // Average waiting and turnaround time
    printf("\nAverage Waiting Time: %.2f", (total_wait/n));
    printf("\nAverage Turnaround Time: %.2f", (total_turnaround/n));
}

void display(struct Process p[], int n) {
    int i;
    
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time");
    for(i = 0; i < n; i++) {
        printf("\n%d\t%d\t\t%d\t\t%d\t\t%d", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    }
}

void sortArrival(struct Process p[], int n) {
    int i, j;
    struct Process temp;

    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(p[i].arrival > p[j].arrival) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n, i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input process details
    for(i = 0; i < n; i++) {
        printf("\nEnter arrival time and burst time for Process %d: ", i+1);
        p[i].pid = i+1;
        p[i].waiting = 0;
        p[i].turnaround = 0;
        scanf("%d %d", &p[i].arrival, &p[i].burst);
    }

    // Sort processes by arrival time
    sortArrival(p, n);

    // Calculate waiting and turnaround times
    calculateTimes(p, n);

    // Display process details
    display(p, n);

    return 0;
}

