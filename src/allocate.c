#include <stdio.h>

#include "./string.h"

#define FILE_CMD "-f"
#define PROCESS_NUM_CMD "-p"

int main(int argc, char* argv[]){

    //the number of processors
    int num_p = 0;
    //the file contain the information about processes
    FILE *processes;

    //read the command
    int i = 0;
    for(i=0;i<argc;i++){
        if(!strcmp(argv[i],FILE_CMD)){
            processes = fopen(argv[++i],"r");
        }
        else if(!strcmp(argv[i],PROCESS_NUM_CMD)){
            num_p = atoi(argv[++i]);
        }
    }


    //close the file
    fclose(processes);
    return 0;
}