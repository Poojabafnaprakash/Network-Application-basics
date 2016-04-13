#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t processID;
    int num;
    printf("Starting three child processes\n");
    printf("Parent's Process Id is: %d \n", getpid());
    
    for(num=0; num<3; num++)
    {
        //Creates a new process
        processID=fork();
        
        //The process sleeps (Halts)
        sleep(5);
        
        if(processID==0)
        {
            printf("The process ID of child %d: %d and its Parent Process ID: %d \n", num+1, getpid(),getppid());
            fflush(stdout);
            exit(0);
        }
        else if(processID<0)
        {
            printf("Failed to create the process. Please try again");
            exit(-1);
        }
    }//closing For Loop
    return 0;
    
}//closing Main()
