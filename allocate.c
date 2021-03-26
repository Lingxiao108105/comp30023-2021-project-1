#include <stdio.h>
#include <stdlib.h>

#include "./struct.h"
#include "./string.h"
#include "./scheduler.h"

#define FILE_CMD "-f"
#define PROCESS_NUM_CMD "-p"

int main(int argc, char* argv[]){

    //the number of processors
    int num_p = 0;
    //the file contain the information about processes
    FILE *process_file;
    //the scheduler
    Scheduler *scheduler;

    //read the command
    int i = 0;
    for(i=0;i<argc;i++){
        if(!strcmp(argv[i],FILE_CMD)){
            process_file = fopen(argv[++i],"r");
        }
        else if(!strcmp(argv[i],PROCESS_NUM_CMD)){
            num_p = atoi(argv[++i]);
        }
    }

    //create a new scheduler
    if((scheduler = create_scheduler(num_p,process_file)) == NULL){
        printf("Empty file!");
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
