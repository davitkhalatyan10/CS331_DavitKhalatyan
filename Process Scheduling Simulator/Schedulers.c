#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

void fcfs(struct Process arr[], int size) {
    int time = 0;
    struct Process temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].arrival_time > arr[j + 1].arrival_time) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("=== First Come First Served (FCFS) ===\nGantt Chart: | ");
    for (int i = 1; i < size + 1; i++) {
        printf("P%d | ", i);
    }
    printf("\nPID    AT    BT    WT    TAT    RT\n");
    struct Process p;
    double avg_wait = 0;
    double avg_tat = 0;
    double avg_rt = 0;
    for (int i = 0; i < size; i++) {
        p = arr[i];
        p.response_time = time - p.arrival_time;
        p.waiting_time = time - p.arrival_time;
        time += p.burst_time;
        p.turnaround_time = time - p.arrival_time;
        avg_wait += p.waiting_time;
        avg_tat += p.turnaround_time;
        avg_rt += p.response_time;
        printf("%d      %d      %d     %d     %d     %d\n",
            p.pid, p.arrival_time, p.burst_time, p.waiting_time, p.turnaround_time, p.response_time);
    }
    avg_wait /= size;
    avg_tat /= size;
    avg_rt /= size;
    printf("\nAverage Waiting Time: %f\n", avg_wait);
    printf("Average Turnaround Time: %f\n", avg_tat);
    printf("Average Response Time: %f\n", avg_rt);
};

void sjf(struct Process arr[], int size) {
    int time = 0;
    struct Process temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].burst_time > arr[j + 1].burst_time) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("=== Shortest Job First (SJF) ===\nGantt Chart: | ");
    for (int i = 1; i < size + 1; i++) {
        printf("P%d | ", i);
    }
    printf("\nPID    AT    BT    WT    TAT    RT\n");
    struct Process p;
    double avg_wait = 0;
    double avg_tat = 0;
    double avg_rt = 0;
    for (int i = 0; i < size; i++) {
        p = arr[i];
        p.response_time = time - p.arrival_time;
        p.waiting_time = time - p.arrival_time;
        time += p.burst_time;
        p.turnaround_time = time - p.arrival_time;
        avg_wait += p.waiting_time;
        avg_tat += p.turnaround_time;
        avg_rt += p.response_time;
        printf("%d      %d      %d     %d     %d     %d\n",
            p.pid, p.arrival_time, p.burst_time, p.waiting_time, p.turnaround_time, p.response_time);
    }
    avg_wait /= size;
    avg_tat /= size;
    avg_rt /= size;
    printf("\nAverage Waiting Time: %f\n", avg_wait);
    printf("Average Turnaround Time: %f\n", avg_tat);
    printf("Average Response Time: %f\n", avg_rt);
};

int main() {
    printf("Enter the number of processes: ");
    int n;
    scanf(" %d", &n);
    struct Process arr[n];
    int a, b;
    for (int i = 0; i < n; i++) {
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &a, &b);
        arr[i].pid = i;
        arr[i].arrival_time = a;
        arr[i].burst_time = b;
    }
    int alg;
    printf("Enter 1 for FCFS and 2 for SJF Schedulers: ");
    scanf(" %d", &alg);
    if (alg == 1) {
        fcfs(arr, n);
    }
    else if (alg == 2) {
        sjf(arr, n);
    }
    return 0;
}