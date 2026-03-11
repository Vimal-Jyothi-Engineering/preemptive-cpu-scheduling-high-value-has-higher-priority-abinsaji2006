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

int main() {

    Process procs[MAX_PROC];
    int n = 0;

    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%s %d %d %d",
              procs[i].name,
              &procs[i].arrival,
              &procs[i].burst,
              &procs[i].priority);

        procs[i].remaining = procs[i].burst;
    }

    int time = 0;
    int done = 0;
    int finished[MAX_PROC] = {0};

    while(done < n) {

        int idx = -1;
        int highest = 9999;

        for(int i = 0; i < n; i++) {

            if(!finished[i] && procs[i].arrival <= time) {

                if(procs[i].priority < highest) {
                    highest = procs[i].priority;
                    idx = i;
                }

                else if(procs[i].priority == highest) {
                    if(procs[i].arrival < procs[idx].arrival)
                        idx = i;
                }
            }
        }

        if(idx == -1) {
            time++;
        }
        else {

            procs[idx].remaining--;
            time++;

            if(procs[idx].remaining == 0) {

                procs[idx].finish = time;

                procs[idx].turnaround =
                    procs[idx].finish - procs[idx].arrival;

                procs[idx].waiting =
                    procs[idx].turnaround - procs[idx].burst;

                finished[idx] = 1;
                done++;
            }
        }
    }

    printf("Waiting Time:\n");
    for(int i = 0; i < n; i++)
        printf("%s %d\n", procs[i].name, procs[i].waiting);

    printf("Turnaround Time:\n");
    for(int i = 0; i < n; i++)
        printf("%s %d\n", procs[i].name, procs[i].turnaround);

    double total_wt = 0;
    double total_tat = 0;

    for(int i = 0; i < n; i++) {
        total_wt += procs[i].waiting;
        total_tat += procs[i].turnaround;
    }

    printf("Average Waiting Time: %.2f\n", total_wt/n);
    printf("Average Turnaround Time: %.2f\n", total_tat/n);

    return 0;
}
