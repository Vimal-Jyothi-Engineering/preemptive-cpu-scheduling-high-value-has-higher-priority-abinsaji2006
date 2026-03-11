#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROC 100

typedef struct {
    char name[20];
    int arrival;
    int burst;
    int priority;
    int remaining;
    int finish;
    int waiting;
    int turnaround;
} Process;

int main(void) {
    Process procs[MAX_PROC];
    int n = 0;
    char buf[256];

    // Flexible Input Parsing
    if (scanf("%s", buf) != 1) return 0;

    if (buf[0] >= '0' && buf[0] <= '9') {
        n = atoi(buf);
        for (int i = 0; i < n; i++) {
            scanf("%s %d %d %d", procs[i].name, &procs[i].arrival, &procs[i].burst, &procs[i].priority);
            procs[i].remaining = procs[i].burst;
        }
    } else {
        int arr, bur, pri;
        do {
            if (scanf("%d %d %d", &arr, &bur, &pri) == 3) {
                strcpy(procs[n].name, buf);
                procs[n].arrival = arr;
                procs[n].burst = bur;
                procs[n].priority = pri;
                procs[n].remaining = bur;
                n++;
            }
        } while (scanf("%s", buf) == 1);
    }

    if (n == 0) return 0;

    int done = 0, time = 0;
    int finished[MAX_PROC] = {0};

    // Core Scheduling Loop
    while (done < n) {
        int idx = -1;
        int highest_prio = -1;

        for (int i = 0; i < n; i++) {
            if (procs[i].arrival <= time && !finished[i]) {
                // Higher number = Higher Priority
                if (procs[i].priority > highest_prio) {
                    highest_prio = procs[i].priority;
                    idx = i;
                } 
                // Tie-breaker: Earlier arrival time
                else if (procs[i].priority == highest_prio) {
                    if (procs[i].arrival < procs[idx].arrival) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            procs[idx].remaining--;
            time++;
            if (procs[idx].remaining == 0) {
                procs[idx].finish = time;
                procs[idx].turnaround = procs[idx].finish - procs[idx].arrival;
                procs[idx].waiting = procs[idx].turnaround - procs[idx].burst;
                finished[idx] = 1;
                done++;
            }
        } else {
            time++; // CPU Idle
        }
    }

    // Output
    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) printf("%s %d\n", procs[i].name, procs[i].waiting);
    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) printf("%s %d\n", procs[i].name, procs[i].turnaround);

    double avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += procs[i].waiting;
        avg_tat += procs[i].turnaround;
    }
    printf("Average Waiting Time: %.2f\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}
