#ifndef _STRUCT_H
#define _STRUCT_H

#include <stdlib.h>
#include <stdio.h>

/**include all the stucture
*/

// Node
typedef struct node{
    void *data;
    struct node *next;
}Node;

// Priority Queue
typedef struct pqueue{
    Node *head;
    int length;
}Pqueue;

//structure of process
typedef struct process{
    int pid;
    char parallelisable;
    //child_pid is -1 if it is not a child process
    int child_pid;
    int status;
    Pqueue *children;
    int remaining_time;  

    //the information for performance sttatistics  

    int coming_time;
    //the required time for the whole process, not subprocess
    int required_time;
    int finish_time;
}Process;

//structure of processor
typedef struct processor{
    int cid;
    int remaining_time;
    Pqueue *processes;
}Processor;

//structure of scheduler
typedef struct scheduler{
    int curr_time;
    int num_proc_left;
    int count_processor;
    Pqueue *finished_processes;
    Process *upcoming_process;
    Pqueue *processores;
    Pqueue *execution_transcript_buffer;
    FILE *process_file;
}Scheduler;


//structure of Execution transcript buffer
typedef struct buffer{
    int status;
    int pid;
    int child_pid;
    int remaining_time;
    int cid;
}Buffer;


#endif