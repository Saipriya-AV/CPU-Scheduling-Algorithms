#include <stdio.h>
#include <stdlib.h>
#define maxpro 10

int ljf_pr[10];
int ljf_bt[10];

struct rr_pr {
  int arrival_t;
  int burst_t;
  int remain_time;
} p[10];

struct sjf_pr {
    int pid;         
    int sj_bt;   
    int sj_wt; 
    int sj_tt;    
} sj_p[10];


struct fcfs_pr {
    int pid;
    int fcfs_bt;
};

struct fcfs_q {
    int front, rear;
    struct fcfs_pr data[maxpro];
};



int main() {
    int choice;
    int no;
    while (choice!=5) {
        printf("\n-----------------------------------");
        printf("\nCPU Scheduling Simulation using C");
        printf("\n-----------------------------------");
        printf("\n1. Round Robin Scheduling\n2. FCFS Scheduling\n3. Shortest Job First Scheduling\n4. Longest Job First Scheduling\n5. Exit");
        printf("\n-----------------------------------");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                round_robin();
                break;
            case 2:
                fcfs();
                break;
            case 3:
                sjf();
                break;
            case 4:
                printf("Enter the number of processes: ");
                scanf("%d", &no);
                for(int i=0;i<no;i++)
                {
                    printf("Enter Process ID and Burst time: ");
                    scanf("%d%d", &ljf_pr[i],&ljf_bt[i]);
                }
                printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
                ljf(no, ljf_pr, ljf_bt);
                break;
            case 5:
                return(0);
                break;
            default:
                printf("Invalid choice. Try again.");
        }
    }
    return 0;
}


void init_queue(struct fcfs_q* q) {
    q->front = q->rear = -1;
}

int is_empty(struct fcfs_q* q) {
    return q->front == -1;
}

int is_full(struct fcfs_q* q) {
    return (q->rear + 1) % maxpro == q->front;
}

void enqueue(struct fcfs_q* q, struct fcfs_pr item) {
    if (is_full(q)) {
        printf("Queue is full.\n");
        return;
    }

    q->rear = (q->rear + 1) % maxpro;
    q->data[q->rear] = item;
    if (q->front == -1)
        q->front = q->rear;
}

struct fcfs_pr dequeue(struct fcfs_q* q) {
    if (is_empty(q)) {
        printf("Queue is empty.\n");
        exit(EXIT_FAILURE);
    }

    struct fcfs_pr item = q->data[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front = (q->front + 1) % maxpro;
    return item;
}

void round_robin() {
    int cnt,t,remain,flag=0;
    int n, tq,i;
    float wt=0,tat=0;
    printf("Enter the total number of processes:");
    scanf("%d",&n);
    for(i=0;i<n;i++)
        {
            printf("Enter Arrival Time and Burst Time for Process %d :",i+1);
            scanf("%d",&p[i].arrival_t);
            scanf("%d",&p[i].burst_t);
            p[i].remain_time = p[i].burst_t;
        }
    printf("Enter Time Quantum:");
    scanf("%d",&tq);
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    remain=n;
    for(t=0,cnt=0;remain!=0;)
    {
        if(p[cnt].remain_time <= tq && p[cnt].remain_time > 0)
        {
            t += p[cnt].remain_time;
            p[cnt].remain_time = 0;
            flag=1;
        }
        else if(p[cnt].remain_time > 0)
        {
            p[cnt].remain_time -= tq;
            t += tq;
        }

        
        if(p[cnt].remain_time == 0 && flag==1)
        {
            remain--;
            printf("P[%d]\t\t%d\t\t%d\t\t%d\n",cnt+1,p[cnt].burst_t,t-p[cnt].arrival_t-p[cnt].burst_t,t-p[cnt].arrival_t);
            wt += t-p[cnt].arrival_t-p[cnt].burst_t;
            tat += t-p[cnt].arrival_t;
            flag=0;
        }

        if(cnt==n-1)
        {
            cnt=0;
        }
            
        else if(p[cnt+1].arrival_t <= t)
        {
            cnt++;
        }
            
        else
        {
            cnt=0;
        }
            
    }
    printf("\nAverage Waiting Time= %f\n",wt/n);
    printf("Avg Turnaround Time = %f",tat/n);
}

void fcfs() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct fcfs_q queue;
    init_queue(&queue);

    for (int i = 0; i < n; i++) {
        struct fcfs_pr p;
        printf("Enter process ID and Burst time: ");
        scanf("%d%d", &p.pid,&p.fcfs_bt);
        enqueue(&queue, p);
    }
    int current_time = 0;
    int waiting_time = 0;
    int turnaround_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        struct fcfs_pr current_process = dequeue(&queue);
        current_time += current_process.fcfs_bt;
        waiting_time = current_time - current_process.fcfs_bt;
        turnaround_time = current_time;
        total_waiting_time += waiting_time;
        total_turnaround_time += turnaround_time;
        printf(" P%d\t\t%d\t\t%d\t\t%d\n", current_process.pid, current_process.fcfs_bt,waiting_time, turnaround_time);
    }
    printf("Average Waiting Time: %.2f\n", (float) total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float) total_turnaround_time / n);
}

int sort_ljf(int n, int ljf_bt[]) {
    int i, max = 0, maxi;
    for (i = 0; i < n; i++) {
        if (ljf_bt[i] > max) {
            max = ljf_bt[i];
            maxi = i;
        }
    }
    return maxi;
}
void ljf(int n, int ljf_pr[], int ljf_bt[]){
    int i, j, time = 0, ljf_rmt[n], ljf_wt[n], ljf_tt[n];
    float ljf_awt, ljf_attt;
    //Initialize remaining time array
    for (i = 0; i < n; i++) {
        ljf_rmt[i] = ljf_bt[i];
    }
    //Process execution
    for (i = 0; i < n; i++) {
        int nextJob = sort_ljf(n, ljf_rmt);
        ljf_rmt[nextJob] = 0;
        for (j = 0; j < ljf_bt[nextJob]; j++) {
            time++;
        }
        //Calculation waiting time and turn around time
        ljf_wt[nextJob] = time - ljf_bt[nextJob];
        ljf_tt[nextJob] = time;
        printf(" P%d\t\t%d\t\t%d\t\t%d\n",ljf_pr[nextJob],ljf_bt[nextJob],ljf_wt[nextJob],ljf_tt[nextJob]);
    }

    //Calculation average waiting time and average turn around time
    float sumWaiting = 0.0, sumTurnAround = 0.0;
    for (i = 0; i < n; i++) {
        sumWaiting += ljf_wt[i];
        sumTurnAround += ljf_tt[i];
        
    }
    ljf_awt = sumWaiting / n;
    ljf_attt = sumTurnAround / n;
    printf("Average waiting time: %f\n", ljf_awt);
    printf("Average turn around time: %f\n", ljf_attt);
}


void sj_sort_bt(int n) {
    struct sjf_pr temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (sj_p[j].sj_bt > sj_p[j+1].sj_bt) {
                temp = sj_p[j];
                sj_p[j] = sj_p[j+1];
                sj_p[j+1] = temp;
            }
        }
    }
}
void sjf() {
    int n;
    float sj_avgwt = 0.0;
    float sj_avgtt = 0.0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &sj_p[i].sj_bt);
        sj_p[i].pid = i+1;
    }
    sj_sort_bt(n);
    // Calculation of waiting time and turnaround time

    sj_p[0].sj_wt = 0;
    sj_p[0].sj_tt = sj_p[0].sj_bt;
    for (int i = 1; i < n; i++) {
        sj_p[i].sj_wt = sj_p[i-1].sj_wt + sj_p[i-1].sj_bt;
        sj_p[i].sj_tt = sj_p[i].sj_wt + sj_p[i].sj_bt;
    }
    
    
    for (int i = 0; i < n; i++) {
        sj_avgwt += sj_p[i].sj_wt;
        sj_avgtt += sj_p[i].sj_tt;
    }
    sj_avgwt /= n;
    sj_avgtt /= n;
    

    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf(" P%d\t\t%d\t\t%d\t\t%d\n", sj_p[i].pid, sj_p[i].sj_bt,
               sj_p[i].sj_wt, sj_p[i].sj_tt);
    }
    printf("\nAverage Waiting Time: %.2f", sj_avgwt);
    printf("\nAverage Turnaround Time: %.2f", sj_avgtt);
}