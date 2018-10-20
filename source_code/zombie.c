#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    printf("Forking a child process\n");

    if ( (pid = fork()) == 0){
        printf("In the child. Process ID: %i, Exiting!\n", getpid());
        exit(1);
    }

    printf("Looping .... forever ....\n");
    printf("Parent pid: %i\n", getpid());
    while(1){
    }
    return 0;
}
