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

    int time=0,completed=0;
    int done[MAX]={0};

    while(completed<n){

        int idx=-1;
        int best=-1;

        for(int i=0;i<n;i++){

            if(!done[i] && p[i].arrival<=time){

                if(p[i].priority>best){
                    best=p[i].priority;
                    idx=i;
                }
            }
        }

        if(idx==-1){
            time++;
            continue;
        }

        p[idx].remaining--;
        time++;

        if(p[idx].remaining==0){

            p[idx].finish=time;

            p[idx].turnaround=
            p[idx].finish-p[idx].arrival;

            p[idx].waiting=
            p[idx].turnaround-p[idx].burst;

            done[idx]=1;
            completed++;
        }
    }

    printf("Waiting Time:\n");
    for(int i=0;i<n;i++)
        printf("%s %d\n",p[i].name,p[i].waiting);

    printf("Turnaround Time:\n");
    for(int i=0;i<n;i++)
        printf("%s %d\n",p[i].name,p[i].turnaround);

    double totalw=0,totalt=0;

    for(int i=0;i<n;i++){
        totalw+=p[i].waiting;
        totalt+=p[i].turnaround;
    }

    printf("Average Waiting Time: %.2f\n",totalw/n);
    printf("Average Turnaround Time: %.2f\n",totalt/n);

    return 0;
}
