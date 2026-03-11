#include <stdio.h>

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
    int n;

    scanf("%d",&n);

    for(int i=0;i<n;i++){
        scanf("%s %d %d %d",
              p[i].name,
              &p[i].arrival,
              &p[i].burst,
              &p[i].priority);

        p[i].remaining = p[i].burst;
    }

    int time = 0;
    int completed = 0;
    int done[MAX] = {0};

    while(completed < n){

        int idx = -1;
        int best_priority = -1;

        for(int i=0;i<n;i++){

            if(!done[i] && p[i].arrival <= time){

                if(p[i].priority > best_priority){
                    best_priority = p[i].priority;
                    idx = i;
                }
            }
        }

        if(idx == -1){
            time++;
            continue;
        }

        /* execute for 1 unit (preemptive) */
        p[idx].remaining--;
        time++;

        if(p[idx].remaining == 0){

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
    for(int i=0;i<n;i++)
        printf("%s %d\n",p[i].name,p[i].waiting);

    printf("Turnaround Time:\n");
    for(int i=0;i<n;i++)
        printf("%s %d\n",p[i].name,p[i].turnaround);

    double total_w=0,total_t=0;

    for(int i=0;i<n;i++){
        total_w += p[i].waiting;
        total_t += p[i].turnaround;
    }

    printf("Average Waiting Time: %.2f\n",total_w/n);
    printf("Average Turnaround Time: %.2f\n",total_t/n);

    return 0;
}
