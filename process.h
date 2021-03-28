#ifndef _PROCESS_H
#define _PROCESS_H

#include "./struct.h"
#include "./pqueue.h"

#define STATUS_WAIT 0
#define STATUS_RUN 1
#define STATUS_FINISH 2
#define WORD_RUN "RUNNING"
#define WORD_FINISH "FINISHED"
#define PARALLELISABLE 'p'
#define NOTPARALLELISABLE 'n'


/**create a new process
 */
Process *create_process(int pid, char parallelisable, int child_pid, Pqueue *childs,int coming_time, int required_time, int remaining_time);
/**free a process
 */
void free_process(void *process);
/**start a process
 * return 1 if the status of process switch from wait to run
 * 0 otherwise
 */
int start_process(Process *process);
/**run a process
 * return -1 if the status of process is wait
 * 0 otherwise
 */
int run_process(Process *process);
/**switch the status of a process to wait
 */
void wait_process(Process *process);
/**check the status of a process
 */
int check_process(Process *process);
/**compare two process
 */
int compare_process(void *p1, void *p2);
/**compare two process
 * process with longer remaining time is smaller
 */
int compare_process_customize(void *pv1, void *pv2);

#endif