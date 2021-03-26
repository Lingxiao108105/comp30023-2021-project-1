#include <stdio.h>

#include "./process.h"
#include "./struct.h"

/**create a new process
 */
Process *create_process(int pid, char parallelisable, int child_pid, Pqueue *children,int coming_time, int required_time, int remaining_time){
    Process *new_process = (Process *)malloc(sizeof(Process));
    new_process->pid = pid;
    new_process->parallelisable = parallelisable;
    new_process->child_pid = child_pid;
    new_process->status = STATUS_WAIT;
    new_process->children = children;
    new_process->coming_time = coming_time;
    new_process->required_time = remaining_time;
    new_process->remaining_time = remaining_time;
    return new_process;
}

/**free a process
 */
void free_process(void *void_process){
    Process *process = (Process *)void_process;
    free_pqueue(process->children,&free_process);
    free(process);
}

/**start a process
 * return 1 if the status of process switch from wait to run
 * 0 otherwise
 */
int start_process(Process *process){
    if(process->status == STATUS_WAIT){
        process->status = STATUS_RUN;
        return 1;
    }
    return 0;
}

/**run a process
 * return -1 if the status of process is wait
 * 0 otherwise
 */
int run_process(Process *process){
    if(process->status == STATUS_WAIT){
        return -1;
    }
    (process->remaining_time)--;

    //if the remaining time is 0, switch the status to finish
    if(process->remaining_time==0){
        process->status = STATUS_FINISH;
    }
    return 0;
}

/**switch the status of a process to wait
 */
void wait_process(Process *process){
    process->status = STATUS_WAIT;
}

/**check the status of a process
 */
int check_process(Process *process){
    return process->status;
}


/**compare two process
 */
int compare_process(void *pv1, void *pv2){
    Process *p1 = (Process *)pv1;
    Process *p2 = (Process *)pv2;
    if(p1->remaining_time < p2->remaining_time){
        return -1;
    }
    else if(p1->remaining_time == p2->remaining_time){
        if(p1->pid < p2->pid){
            return -1;
        }
        else if(p1->pid == p2->pid){
            if(p1->child_pid < p2->child_pid){
                return -1;
            }
            else if(p1->child_pid == p2->child_pid){
                return 1;
            }
            else{
                return 1;
            }
        }
        else{
            return 1;
        }
    }
    else{
        return 1;
    }
}
