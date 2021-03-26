#include <stdio.h>

#include "./processor.h"

/**create a new processor
 */
Processor *create_processor(int cid){
    Processor *new_processor = (Processor *)malloc(sizeof(Processor));
    new_processor->cid = cid;
    new_processor->remaining_time = 0;
    new_processor->processes = create_pqueue();
    return new_processor;
}

/**free a processor
 */
void free_processor(void *void_processor){
    if(void_processor == NULL){
        return;
    }
    Processor *processor = (Processor *)void_processor;
    free_pqueue(processor->processes,&free_process);
    free(processor);
}

/**start a processor
 * return 1 if the status of first process in processor switch from wait to run
 * 0 otherwise
 */
int start_processor(Processor *processor){
    return start_process(head(processor->processes));
}

/**run the processor
 * return the change in remaining time
 */
int run_processor(Processor *processor){
    //if processor is empty, just skip
    if(isEmpty(processor->processes)){
        return 0;
    }
    run_process(head(processor->processes));
    (processor->remaining_time)--;
    return -1;
}



/**check the status of the first process in processor
 * return -1 if processor is empty
 */
int check_processor(Processor *processor){
    if(isEmpty(processor->processes)){
        return -1;
    }
    return check_process(head(processor->processes));
}

/**allocate a process to processor
 */
void allocate_process(Processor *processor,Process *process){
    push_data(processor->processes,process,&compare_process);
    processor->remaining_time += process->remaining_time;
    //check whether the first process is changed
    if(process == head(processor->processes) && processor->remaining_time!=process->remaining_time){
        //change the status of provious first process to wait
        wait_process(processor->processes->head->next->data);
    }
}


/**compare two processor
 */
int compare_processor(void *pv1, void *pv2){
    Processor *p1 = (Processor *)pv1;
    Processor *p2 = (Processor *)pv2;
    if(p1->remaining_time < p2->remaining_time){
        return -1;
    }
    else if(p1->remaining_time == p2->remaining_time){
        if(p1->cid < p2->cid){
            return -1;
        }
        else if(p1->cid == p2->cid){
            return 0;
        }
        else{
            return 1;
        }
    }
    else{
        return 1;
    }
}