#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[10];
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

    while (scanf("%s %d %d %d", p[n].name,
           &p[n].arrival, &p[n].burst, &p[n].priority) == 4) {

        p[n].remaining = p[n].burst;
        n++;
    }

    int time = 0;
    int completed = 0;
    int done[MAX] = {0};

    while (completed < n) {

        int idx = -1;
        int highest = -1;

        for (int i = 0; i < n; i++) {

            if (!done[i] && p[i].arrival <= time) {

                if (p[i].priority > highest) {
                    highest = p[i].priority;
                    idx = i;
                }

                else if (p[i].priority == highest) {
                    if (p[i].arrival < p[idx].arrival)
                        idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].remaining--;
        time++;

        if (p[idx].remaining == 0) {

            p[idx].finish = time;
            p[idx].turnaround = p[idx].finish - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;

            done[idx] = 1;
            completed++;
        }
    }

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++)
        printf("%s %d\n", p[i].name, p[i].waiting);

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++)
        printf("%s %d\n", p[i].name, p[i].turnaround);

    double avg_w = 0, avg_t = 0;

    for (int i = 0; i < n; i++) {
        avg_w += p[i].waiting;
        avg_t += p[i].turnaround;
    }

    printf("Average Waiting Time: %.2f\n", avg_w / n);
    printf("Average Turnaround Time: %.2f\n", avg_t / n);

    return 0;
}
