#ifndef _SCHEDULER_H
#define _SCHEDULER_H


#define SCHE_STATUS_END 0
#define SCHE_STATUS_RUN 1

#include "./struct.h"
#include "./string.h"
#include "./process.h"
#include "./processor.h"
#include "./pqueue.h"

/**the scheduler for allocate the process to processor
*/

/**create an empty scheduler
 * and read one process from file
 * return NULL if file is empty
 */
Scheduler *create_scheduler(int num_p,FILE *process_file);
/**release the scheduler
 */
void free_scheduler(Scheduler *scheduler);
/**the algorithm to allocate a process to a processor
 * return 1 if schedule a process
 * return -1 if upcoming process is NULL
 * return 0 otherwise
 */
int schedule_process(Scheduler *scheduler);
/**read next process from file
 * return the process it create
 * return NULL if reach the end of file
 */
Process *read_next_process(FILE *process_file);
/**split the process which is parallelisable
 */
//Pqueue *split_process();
/**run all the processor in the cpu
 * return the status of scheduler after running
 */
int run_scheduler(Scheduler *scheduler);
/**end a process
 */
void finish_a_process(Scheduler *scheduler, Processor *curr_processor, Process *process);
/**print the performance statistics to stdout
 */
void performance_statistics(Scheduler *scheduler);
/**create a Execution transcript
 */
Buffer *create_buffer(int status, int pid, int child_pid, int remaining_time, int cid, int proc_remaining);
/**free the Execution transcript
 */
void free_buffer(void *buffer);
/**compare two Execution information
 */
int compare_buffer(void *b1,void *b2);
/**print all the buffers
 */
void print_buffers(Scheduler *scheduler);

#endif
