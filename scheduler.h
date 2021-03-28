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
Scheduler *create_scheduler(int num_p,FILE *process_file, int customize);
/**release the scheduler
 */
void free_scheduler(Scheduler *scheduler);
/**the algorithm to allocate a process to a processor
 * return 1 if schedule a process
 * return -1 if upcoming process is NULL
 * return 2 if using customized schedule algorithm
 * return 0 otherwise
 */
int schedule_process(Scheduler *scheduler);
/**read next process from file
 * return the process it create
 * return NULL if reach the end of file
 */
Process *read_next_process(FILE *process_file);
/**compute the split number of a parallelisable process and allocate its subprocesses
 */
void compute_split_num(Scheduler *scheduler, Process *process);
/**split the process which is parallelisable
 * and push allocate them
 * will treat process as non-parallelisable while split number < 2
*/
void split_process(Scheduler *scheduler, Process *process, int split_num);
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
Buffer *create_buffer(int status, unsigned int pid, int child_pid, unsigned int remaining_time, int cid);
/**free the Execution transcript
 */
void free_buffer(void *buffer);
/**compare two Execution information
 */
int compare_buffer(void *b1,void *b2);
/**print all the buffers
 */
void print_buffers(Scheduler *scheduler);
/**customize algorithm
 */
void customized_schedule_algorithm(Scheduler *scheduler);
/**check whether there is an empty processor in priority queue
 * return 1 if there is an empty processor
 */
int check_empty_processor(Pqueue *processores);
/**compute total remaining time among all the processores and processes
 */
unsigned int total_remaining_time(Pqueue *processores, Pqueue *processes);

#endif
