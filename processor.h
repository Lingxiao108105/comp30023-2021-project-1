#ifndef _PROCESSOR_H
#define _PROCESSOR_H


#include "./struct.h"
#include "./process.h"
#include "./pqueue.h"

/**create a new processor
 */
Processor *create_processor(int cid);
/**free a processor
 */
void free_processor(void *processor);
/**start a processor
 * return 1 if the status of first process in processor switch from wait to run
 * 0 otherwise
 */
int start_processor(Processor *processor);
/**run the processor
 */
int run_processor(Processor *processor);
/**check the status of the first process in processor
 */
int check_processor(Processor *processor);
/**allocate a process to processor
 */
void allocate_process(Processor *processor,Process *process);
/**compare two processor
 */
int compare_processor(void *p1, void *p2);


#endif