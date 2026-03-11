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

    if (scanf("%s", buf) != 1) return 0;

    if (buf[0] >= '0' && buf[0] <= '9') {
        int count = atoi(buf);
        for (int i = 0; i < count; i++) {
            if (scanf("%s %d %d %d", procs[n].name, &procs[n].arrival, &procs[n].burst, &procs[n].priority) == 4) {
                procs[n].remaining = procs[n].burst;
                n++;
            }
        }
    } else {
        strcpy(procs[n].name, buf);
        if (scanf("%d %d %d", &procs[n].arrival, &procs[n].burst, &procs[n].priority) == 3) {
            procs[n].remaining = procs[n].burst;
            n++;
            while (scanf("%s %d %d %d", procs[n].name, &procs[n].arrival, &procs[n].burst, &procs[n].priority) == 4) {
                procs[n].remaining = procs[n].burst;
                n++;
            }
        }
    }

    if (n == 0) {
        printf("Waiting Time:\nTurnaround Time:\nAverage Waiting Time: 0.00\nAverage Turnaround Time: 0.00\n");
        return 0;
    }

    int done = 0;
    int time = 0;
    int finished[MAX_PROC] = {0};

    int min_arrival = procs[0].arrival;
    for (int i = 1; i < n; i++) {
        if (procs[i].arrival < min_arrival) min_arrival = procs[i].arrival;
    }
    time = min_arrival;

    while (done < n) {
        int idx = -1;
        int highest_pri = -1;

        for (int i = 0; i < n; i++) {
            if (!finished[i] && procs[i].arrival <= time) {
                if (procs[i].priority > highest_pri) {
                    highest_pri = procs[i].priority;
                    idx = i;
                } else if (procs[i].priority == highest_pri) {
                    if (idx == -1 || procs[i].arrival < procs[idx].arrival) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            int next_arrival = -1;
            for (int i = 0; i < n; i++) {
                if (!finished[i]) {
                    if (next_arrival == -1 || procs[i].arrival < next_arrival)
                        next_arrival = procs[i].arrival;
                }
            }
            time = next_arrival;
        } else {
            procs[idx].remaining--;
            time++;

            if (procs[idx].remaining == 0) {
                procs[idx].finish = time;
                procs[idx].turnaround = procs[idx].finish - procs[idx].arrival;
                procs[idx].waiting = procs[idx].turnaround - procs[idx].burst;
                finished[idx] = 1;
                done++;
            }
        }
    }

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) printf("%s %d\n", procs[i].name, procs[i].waiting);

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) printf("%s %d\n", procs[i].name, procs[i].turnaround);

    double total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += procs[i].waiting;
        total_tat += procs[i].turnaround;
    }
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
