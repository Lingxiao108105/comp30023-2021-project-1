#include <stdio.h>
#include <stdlib.h>

#include "./struct.h"
#include "./string.h"
#include "./scheduler.h"

#define FILE_CMD "-f"
#define PROCESS_NUM_CMD "-p"
#define CUSTRUMER "-c"

int main(int argc, char* argv[]){

    //the number of processors
    int num_p = 0;
    //the file contain the information about processes
    FILE *process_file;
    //whether use customize algorithm
    int customize = 0;
    //the scheduler
    Scheduler *scheduler;

    //read the command
    int i = 0;
    for(i=0;i<argc;i++){
        if(!my_strcmp(argv[i],FILE_CMD)){
            process_file = fopen(argv[++i],"r");
        }
        else if(!my_strcmp(argv[i],PROCESS_NUM_CMD)){
            num_p = atoi(argv[++i]);
        }
        else if(!my_strcmp(argv[i],CUSTRUMER)){
            customize = 1;
        }
    }

    //create a new scheduler
    if((scheduler = create_scheduler(num_p,process_file,customize)) == NULL){
        printf("file not exist!");
        return 0;
    };
    //run the scheduler till end
    while(run_scheduler(scheduler)){};
    //release the scheduler
    free_scheduler(scheduler);
    //close the file
    fclose(process_file);
    return 0;
}
