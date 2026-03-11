#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[10];
    int arrival;
    int burst;
    int priority;
    int finish;
    int waiting;
    int turnaround;
} Process;

int main() {

    Process p[MAX];
    int n = 0;

    while (scanf("%s %d %d %d", p[n].name,
           &p[n].arrival, &p[n].burst, &p[n].priority) == 4) {
        n++;
    }

    int completed = 0;
    int time = 0;
    int done[MAX] = {0};

    int min_arrival = p[0].arrival;
    for(int i=1;i<n;i++)
        if(p[i].arrival < min_arrival)
            min_arrival = p[i].arrival;

    time = min_arrival;

    while(completed < n) {

        int idx = -1;
        int highest = -1;

        for(int i=0;i<n;i++) {

            if(!done[i] && p[i].arrival <= time) {

                if(p[i].priority > highest) {
                    highest = p[i].priority;
                    idx = i;
                }

                else if(p[i].priority == highest) {
                    if(p[i].arrival < p[idx].arrival)
                        idx = i;
                }
            }
        }

        if(idx == -1) {
            time++;
            continue;
        }

        time += p[idx].burst;

        p[idx].finish = time;

        p[idx].turnaround =
        p[idx].finish - p[idx].arrival;

        p[idx].waiting =
        p[idx].turnaround - p[idx].burst;

        done[idx] = 1;
        completed++;
    }

    printf("Waiting Time:\n");
    for(int i=0;i<n;i++)
        printf("%s %d\n", p[i].name, p[i].waiting);

    printf("Turnaround Time:\n");
    for(int i=0;i<n;i++)
        printf("%s %d\n", p[i].name, p[i].turnaround);

    double total_w=0,total_t=0;

    for(int i=0;i<n;i++){
        total_w+=p[i].waiting;
        total_t+=p[i].turnaround;
    }

    printf("Average Waiting Time: %.2f\n", total_w/n);
    printf("Average Turnaround Time: %.2f\n", total_t/n);

    return 0;
}
