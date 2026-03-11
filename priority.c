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

    if(scanf("%s", first) != 1) return 0;

    if(first[0] >= '0' && first[0] <= '9') {
        int count = atoi(first);

        for(int i=0;i<count;i++) {
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

    int finished[MAX] = {0};
    int completed = 0;
    int time = 0;

    while(completed < n) {

        int idx = -1;
        int best_priority = -1;

        for(int i=0;i<n;i++) {

            if(!finished[i] && p[i].arrival <= time) {

                if(p[i].priority > best_priority) {
                    best_priority = p[i].priority;
                    idx = i;
                }
                else if(p[i].priority == best_priority) {
                    if(p[i].arrival < p[idx].arrival)
                        idx = i;
                }
            }
        }

        if(idx == -1) {
            time++;
        }
        else {

            p[idx].remaining--;
            time++;

            if(p[idx].remaining == 0) {

                p[idx].finish = time;

                p[idx].turnaround =
                    p[idx].finish - p[idx].arrival;

                p[idx].waiting =
                    p[idx].turnaround - p[idx].burst;

                finished[idx] = 1;
                completed++;
            }
        }
    }

    printf("Waiting Time:\n");
    for(int i=0;i<n;i++)
        printf("%s %d\n", p[i].name, p[i].waiting);

    printf("Turnaround Time:\n");
    for(int i=0;i<n;i++)
        printf("%s %d\n", p[i].name, p[i].turnaround);

    double total_wt = 0;
    double total_tat = 0;

    for(int i=0;i<n;i++) {
        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
    }

    printf("Average Waiting Time: %.2f\n", total_wt/n);
    printf("Average Turnaround Time: %.2f\n", total_tat/n);

    return 0;
}
