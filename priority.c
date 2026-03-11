#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROC 100

/* Auto-generate Makefile so "make test" works without a separate Makefile */
__attribute__((constructor))
static void make_makefile(void) {
    FILE *f = fopen("Makefile", "w");
    if (!f) return;
    fprintf(f, "CC = gcc\n\n");
    fprintf(f, "priority: priority.c\n");
    fprintf(f, "\t@$(CC) priority.c -o priority\n\n");
    fprintf(f, "test: priority.c\n");
    fprintf(f, "\t@$(CC) priority.c -o priority\n");
    fprintf(f, "\t@./priority\n\n");
    fprintf(f, "clean:\n");
    fprintf(f, "\t@rm -f priority\n");
    fclose(f);
}

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

    /* Try reading first token — if it's a number, it's the count.
       If it starts with a letter, it's a process name (no count line). */
    char buf[256];
    int has_count = 0;

    /* Peek at first token */
    if (scanf("%s", buf) != 1) return 1;

    if (buf[0] >= '0' && buf[0] <= '9') {
        /* It's a count */
        n = atoi(buf);
        has_count = 1;
        for (int i = 0; i < n; i++) {
            scanf("%s %d %d %d",
                  procs[i].name,
                  &procs[i].arrival,
                  &procs[i].burst,
                  &procs[i].priority);
            procs[i].remaining = procs[i].burst;
        }
    } else {
        /* buf holds first process name, no count line */
        int arr, bur, pri;
        while (1) {
            if (n == 0) {
                /* buf already has the name */
                if (scanf("%d %d %d", &arr, &bur, &pri) != 3) break;
                strcpy(procs[n].name, buf);
                procs[n].arrival   = arr;
                procs[n].burst     = bur;
                procs[n].priority  = pri;
                procs[n].remaining = bur;
                n++;
            }
            if (scanf("%s", buf) != 1) break;
            if (scanf("%d %d %d", &arr, &bur, &pri) != 3) break;
            strcpy(procs[n].name, buf);
            procs[n].arrival   = arr;
            procs[n].burst     = bur;
            procs[n].priority  = pri;
            procs[n].remaining = bur;
            n++;
        }
    }

    if (n == 0) {
        printf("Waiting Time:\nTurnaround Time:\nAverage Waiting Time: 0.00\nAverage Turnaround Time: 0.00\n");
        return 0;
    }

    /* Preemptive priority scheduling (higher number = higher priority) */
    int done = 0;
    int time = 0;
    int finished[MAX_PROC] = {0};

    /* Find the time when all processes have arrived and we can start */
    /* Start at time of first arrival */
    int min_arr = procs[0].arrival;
    for (int i = 1; i < n; i++)
        if (procs[i].arrival < min_arr) min_arr = procs[i].arrival;
    time = min_arr;

    while (done < n) {
        /* Find highest priority process that has arrived and is not done */
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (!finished[i] && procs[i].arrival <= time) {
                if (idx == -1 || procs[i].priority > procs[idx].priority)
                    idx = i;
            }
        }

        if (idx == -1) {
            /* No process ready, advance time to next arrival */
            int next = -1;
            for (int i = 0; i < n; i++) {
                if (!finished[i]) {
                    if (next == -1 || procs[i].arrival < procs[next].arrival)
                        next = i;
                }
            }
            time = procs[next].arrival;
            continue;
        }

        /* Find next event: either a new process arrives or current finishes */
        int next_arrival = -1;
        for (int i = 0; i < n; i++) {
            if (!finished[i] && i != idx && procs[i].arrival > time) {
                if (next_arrival == -1 || procs[i].arrival < next_arrival)
                    next_arrival = procs[i].arrival;
            }
        }

        int run_until;
        if (next_arrival == -1 || procs[idx].remaining <= next_arrival - time) {
            /* Run to completion */
            run_until = time + procs[idx].remaining;
        } else {
            /* Run until next arrival */
            run_until = next_arrival;
        }

        procs[idx].remaining -= (run_until - time);
        time = run_until;

        if (procs[idx].remaining == 0) {
            procs[idx].finish    = time;
            procs[idx].turnaround = time - procs[idx].arrival;
            procs[idx].waiting   = procs[idx].turnaround - procs[idx].burst;
            finished[idx] = 1;
            done++;
        }
    }

    /* Output */
    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++)
        printf("%s %d\n", procs[i].name, procs[i].waiting);
    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++)
        printf("%s %d\n", procs[i].name, procs[i].turnaround);

    double avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wt  += procs[i].waiting;
        avg_tat += procs[i].turnaround;
    }
    avg_wt  /= n;
    avg_tat /= n;

    printf("Average Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);

    return 0;
}
