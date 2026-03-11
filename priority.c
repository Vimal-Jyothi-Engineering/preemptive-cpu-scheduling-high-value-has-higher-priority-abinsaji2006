#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

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

    Process p[MAX];
    int n = 0;
    char first[20];

    if(scanf("%s", first) != 1)
        return 0;

    if(first[0] >= '0' && first[0] <= '9') {

        int count = atoi(first);

        for(int i = 0; i < count; i++) {
            scanf("%s %d %d %d",
                  p[n].name,
                  &p[n].arrival,
                  &p[n].burst,
                  &p[n].priority);

            p[n].remaining = p[n].burst;
            n++;
        }
    }
    else {

        strcpy(p[n].name, first);

        scanf("%d %d %d",
              &p[n].arrival,
              &p[n].burst,
              &p[n].priority);

        p[n].remaining = p[n].burst;
        n++;

        while(scanf("%s %d %d %d",
                    p[n].name,
                    &p[n].arrival,
                    &p[n].burst,
                    &p[n].priority) == 4) {

            p[n].remaining = p[n].burst;
            n++;
        }
    }

    int time = 0;
    int completed = 0;
    int done[MAX] = {0};

    int min_arrival = p[0].arrival;
    for(int i = 1; i < n; i++)
        if(p[i].arrival < min_arrival)
            min_arrival = p[i].arrival;

    time = min_arrival;

    while(completed < n) {

        int idx = -1;
        int best_priority = -1;

        for(int i = 0; i < n; i++) {

            if(!done[i] && p[i].arrival <= time) {

                if(p[i].priority > best_priority) {
                    best_priority = p[i].priority;
                    idx = i;
                }
                else if(p[i].priority == best_priority) {

                    if(idx == -1 || p[i].arrival < p[idx].arrival)
                        idx = i;
                }
            }
        }

        if(idx == -1) {
            time++;
            continue;
        }

        p[idx].remaining--;
        time++;

        if(p[idx].remaining == 0) {

            p[idx].finish = time;

            p[idx].turnaround =
                p[idx].finish - p[idx].arrival;

            p[idx].waiting =
                p[idx].turnaround - p[idx].burst;

            done[idx] = 1;
            completed++;
        }
    }

    printf("Waiting Time:\n");
    for(int i = 0; i < n; i++)
        printf("%s %d\n", p[i].name, p[i].waiting);

    printf("Turnaround Time:\n");
    for(int i = 0; i < n; i++)
        printf("%s %d\n", p[i].name, p[i].turnaround);

    double total_w = 0;
    double total_t = 0;

    for(int i = 0; i < n; i++) {
        total_w += p[i].waiting;
        total_t += p[i].turnaround;
    }

    printf("Average Waiting Time: %.2f\n", total_w / n);
    printf("Average Turnaround Time: %.2f\n", total_t / n);

    return 0;
}
