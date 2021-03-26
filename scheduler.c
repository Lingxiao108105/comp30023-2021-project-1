#include <stdio.h>
#include <stdlib.h>

#include "./scheduler.h"

/**local function
 */
/**eliminate the 0 at the end of a decimal number
 */
static void eliminate_zero(double num, char *str);

/**create an empty scheduler
 * and read one process from file
 * return NULL if file is empty
 */
Scheduler *create_scheduler(int num_p,FILE *process_file){
    Scheduler *scheduler = (Scheduler *)malloc(sizeof(Scheduler));

    scheduler->curr_time = 0;
    scheduler->count_processor = num_p;
    scheduler->finished_processes = create_pqueue();
    scheduler->upcoming_process = NULL;
    scheduler->processores = create_pqueue();
    scheduler->num_proc_left = 0;
    //create and insert processores into cheduler
    int i = 0;
    for(i=0;i<num_p;i++){
        push_data(scheduler->processores, create_processor(i), &compare_processor);
    }
    scheduler->execution_transcript_buffer = create_pqueue();
    scheduler->process_file = process_file;

    //read process from file and put it in upcoming process
    Process *first_process = read_next_process(scheduler->process_file);
    if(first_process == NULL){
        free_scheduler(scheduler);
        return NULL;
    }
    scheduler->upcoming_process = first_process;

    return scheduler;
}

/**release the scheduler
 */
void free_scheduler(Scheduler *scheduler){
    if(scheduler == NULL){
        return;
    }
    free_process(scheduler->upcoming_process);
    free_pqueue(scheduler->processores,&free_processor);
    free_pqueue(scheduler->execution_transcript_buffer,&free_buffer);
    free_pqueue(scheduler->finished_processes,&free_process);
    free(scheduler);
}

/**the algorithm to allocate a process to a processor
 * return 1 if schedule a process
 * return -1 if upcoming process is NULL
 * return 0 otherwise
 */
int schedule_process(Scheduler *scheduler){
    if(scheduler->upcoming_process == NULL){
        return -1;
    }
    if(scheduler->upcoming_process->coming_time == scheduler->curr_time){
        Pqueue *processes = create_pqueue();
        //read until get a process in come in future
        while(scheduler->upcoming_process != NULL && scheduler->upcoming_process->coming_time == scheduler->curr_time){
            push_data(processes,scheduler->upcoming_process,&compare_process);
            scheduler->upcoming_process = read_next_process(scheduler->process_file);
            (scheduler->num_proc_left)++;
        }
        while(!isEmpty(processes)){
            Process *curr_process = pop(processes);
            //non-parallelisable process
            if(curr_process->parallelisable == NOTPARALLELISABLE || scheduler->count_processor == 1){
                //need to reassign head processor again
                Processor *head_processor = pop(scheduler->processores);
                allocate_process(head_processor,curr_process);
                push_data(scheduler->processores,head_processor,&compare_processor);
            }   
            //parallelisable process 
            else{
                split_process(scheduler,curr_process);
            }
        }
        free_pqueue(processes,&free_process);
        
        return 1;
    }
    return 0;
}

/**read next process from file
 * return the process it create
 * return NULL if reach the end of file
 */
Process *read_next_process(FILE *process_file){
    Process *process;
    //the property of process
    int coming_time;
    int pid;
    int remaining_time;
    char parallelisable;

    //read the process from file
    if(fscanf(process_file,"%d %d %d %c\n", &coming_time, &pid, &remaining_time, &parallelisable)!=EOF){
        process = create_process(pid,parallelisable,-1,NULL,coming_time,remaining_time,remaining_time);
        return process;
    }
    return NULL;
}

/**
split the process which is parallelisable
*/
void split_process(Scheduler *scheduler, Process *process){

    Process *subprocess;
    Pqueue *children = create_pqueue();
    int i;
    int split_num;
    Node *curr_node = scheduler->processores->head;
    Processor *curr_processor;
    //2 processor
    if(scheduler->count_processor == 2){
        split_num = 2;
    }
    //N processor(not today)
    else{
        //split to the minimum number between number of processor and remaining time
        split_num = scheduler->count_processor > process->remaining_time ? process->remaining_time : scheduler->count_processor;
    }


    int remaining_time = process->remaining_time/split_num +1;
    //need to + 1
    if((process->remaining_time)/(double)split_num > process->remaining_time/split_num){
        remaining_time++;
    }
    //for each process, push it into children to relate all subprocess for a process together
    for(i=0;i<split_num;i++,curr_node=curr_node->next){
        curr_processor = curr_node->data;
        subprocess = create_process(process->pid,PARALLELISABLE,i,children,process->coming_time,process->required_time,remaining_time);
        push_data(children,subprocess,&compare_process);
        allocate_process(curr_processor,subprocess);
    }

    if(scheduler->count_processor > 2){
        //sort the processores
        scheduler->processores = pqueue_sort(scheduler->processores, &compare_processor);
    }

    free_process(process);
}



/**run all the processor in the cpu
 * return the status of scheduler after running
 */
int run_scheduler(Scheduler *scheduler){

    schedule_process(scheduler);
    Pqueue *processores = scheduler->processores;
    Node *curr_node = processores->head;
    Processor *curr_processor;
    //run all the processor
    while(curr_node != NULL){
        curr_processor = curr_node->data;
        //if begin a process, add this information to Execution transcript buffer
        if(start_processor(curr_processor)){
            Process *process = head(curr_processor->processes);
            Buffer *buffer = create_buffer(STATUS_RUN,process->pid,process->child_pid,process->remaining_time,curr_processor->cid);
            push_data(scheduler->execution_transcript_buffer,buffer,&compare_buffer);
        }
        //run the processor
        run_processor(curr_processor);
        curr_node = curr_node->next;
    }
    //print all the Execution transcripts
    print_buffers(scheduler);

    
    //after running all the processor, it becomes next second
    scheduler->curr_time ++;

    int re_arange_processes = 0;
    //check the status of all the processor
    curr_node = processores->head;
    while(curr_node != NULL){
        curr_processor = curr_node->data;
        //if the first process is finished, 
        //add this information to Execution transcript buffer if it is process, or it may be subprocess
        if(check_processor(curr_processor) == STATUS_FINISH){
            //maybe we need to rearrange the processores
            re_arange_processes = 1;
            Process *process = head(curr_processor->processes);
            if(process->child_pid != -1){//it is a subprocess
                //pop it out from the Pqueue *children;
                remove_node(process->children,process);
                Pqueue *childern = process->children;
                process->children = NULL;
                //if it is the last subprocess
                if(pqueue_length(childern)==0){
                    finish_a_process(scheduler, curr_processor, process);
                }
                //not the last subprocess
                else{
                    pop(curr_processor->processes);
                    free_process(process);
                }
            }
            else{
                finish_a_process(scheduler, curr_processor, process);
            }
        }
        curr_node = curr_node->next;
    }

    //rearrange the processores
    if(re_arange_processes){
        scheduler->processores = pqueue_sort(scheduler->processores, &compare_processor);
        processores = scheduler->processores;
    }
    
    //print all the Execution transcripts
    print_buffers(scheduler);
    
    //check whether the simulation ended
    //if simulation ends, print performance statistics
    if(scheduler->num_proc_left == 0 && scheduler->upcoming_process == NULL){
        performance_statistics(scheduler);
        return SCHE_STATUS_END;
    }
    return SCHE_STATUS_RUN;

}

/**end a process
 * add this information to Execution transcripts
 * then move this process from processor to finished processes 
 */
void finish_a_process(Scheduler *scheduler, Processor *curr_processor, Process *process){
    (scheduler->num_proc_left)--;

    Buffer *buffer = create_buffer(STATUS_FINISH,process->pid,process->child_pid,process->remaining_time,curr_processor->cid);
    push_data(scheduler->execution_transcript_buffer,buffer,&compare_buffer);

    remove_node(curr_processor->processes,process);
    push_data(scheduler->finished_processes,process,&compare_process);
    process->finish_time = scheduler->curr_time;

}


/**eliminate the 0 at the end of a decimal number
 */
static void eliminate_zero(double num, char *str){
    int i;
    sprintf(str,"%.2f",num);
    for(i=my_strlen(str)-1;i>=0;i--){
        if(str[i]=='0'){
            str[i] = '\0';
        }
        else if(str[i]=='.'){
            str[i] = '\0';
            return;
        }
        else{
            return;
        }
    }
}


/**print the performance statistics to stdout
 */
void performance_statistics(Scheduler *scheduler){
    //average turnaround time = total turnaround time / num of process
    int total_turnaround_time = 0;
    int num_process = 0;
    int curr_turnaround_time;

    //time overhead
    double max_time_overhead = -1;
    double total_time_overhead = 0;
    double curr_time_overhead;

    //loop through all the finished processes to get information
    Node *curr_node = scheduler->finished_processes->head;
    Process *curr_process;
    while(curr_node != NULL){
        curr_process = curr_node->data;

        curr_turnaround_time = curr_process->finish_time - curr_process->coming_time;
        total_turnaround_time += curr_turnaround_time;
        num_process++;
    
        curr_time_overhead = (double)curr_turnaround_time / curr_process->required_time;
        max_time_overhead = curr_time_overhead > max_time_overhead ? curr_time_overhead : max_time_overhead;
        total_time_overhead += curr_time_overhead;

        curr_node = curr_node->next;
    }

    //average time (in seconds, rounded up to an integer) between the time when theprocess completed and when it arrived
    double d_turnaround_time = (double)total_turnaround_time/num_process;
    int turnaround_time = (int)d_turnaround_time;
    //rounded up
    if(d_turnaround_time > turnaround_time){
        turnaround_time++;
    }
    //Time overhead both rounded to the first two decimal points
    double time_overhead = total_time_overhead/num_process + 0.005;
    max_time_overhead += 0.005;

    //print the performance statistics
    printf("Turnaround time %d\n",turnaround_time);

    //eliminate 0 at the end of each number
    char str_max_time_overhead[101];
    eliminate_zero(max_time_overhead,str_max_time_overhead);
    char str_time_overhead[101];
    eliminate_zero(time_overhead,str_time_overhead);
    
    printf("Time overhead %s %s\n",str_max_time_overhead,str_time_overhead);
    printf("Makespan %d\n",scheduler->curr_time);

}

/**create a Execution transcript
 */
Buffer *create_buffer(int status, int pid, int child_pid, int remaining_time, int cid){
    Buffer *buffer = (Buffer *)malloc(sizeof(Buffer));

    buffer->status =  status;
    buffer->pid =  pid;
    buffer->child_pid = child_pid;
    buffer->remaining_time = remaining_time;
    buffer->cid = cid;

    return buffer;
}

/**free the Execution transcript
 */
void free_buffer(void *buffer){
    if(buffer != NULL){
        free(buffer);
    }
}

/**compare two Execution information
 */
int compare_buffer(void *bv1,void *bv2){
    Buffer *b1 = (Buffer *)bv1;
    Buffer *b2 = (Buffer *)bv2;
    if(b1->status ==  b2->status){
        if(b1->cid < b2->cid){
            return -1;
        }
        else{
            return 1;
        }
    }
    else if(b1->status == STATUS_FINISH){
        return -1;
    }
    else{
        return 1;
    }
}

/**print all the buffers
 */
void print_buffers(Scheduler *scheduler){
    Pqueue *execution_transcript_buffer = scheduler->execution_transcript_buffer;
    Buffer * buffer;
    //pop all the information out
    while(!isEmpty(execution_transcript_buffer)){
        buffer = pop(execution_transcript_buffer);
        //print this buffer
        //print the RUNNING
        if(buffer->status == STATUS_RUN){
            if(buffer->child_pid == -1){//it is not a subprocess
                printf("%d,RUNNING,pid=%d,remaining_time=%d,cpu=%d\n",scheduler->curr_time,buffer->pid,buffer->remaining_time,buffer->cid);
            }
            else{//subprocess
                printf("%d,RUNNING,pid=%d.%d,remaining_time=%d,cpu=%d\n",scheduler->curr_time,buffer->pid,buffer->child_pid,buffer->remaining_time,buffer->cid);
            }
        }
        //print the FINISHED
        else{
            printf("%d,FINISHED,pid=%d,proc_remaining=%d\n",scheduler->curr_time,buffer->pid,scheduler->num_proc_left);
        }
        //release the buffer
        free_buffer(buffer);
    }
}

