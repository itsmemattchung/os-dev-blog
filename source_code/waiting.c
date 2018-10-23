#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define SLEEP_TIME 10

int main(int argc, char *argv[])
{
    pid_t pid;

    printf("Parent pid: %i\n", getpid());

    if ( (pid = fork()) == 0){
	printf("Child pid: %d\n", getpid());

	printf("Sleeping for %i seconds\n ... ", SLEEP_TIME);
	sleep(SLEEP_TIME);

	printf("Done sleeping\n");
    }


    return 0;
}
