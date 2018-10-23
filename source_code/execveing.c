#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[])
{
    pid_t pid;
    int child_status;

    printf("Forking a child process from parent pid %d\n", getpid());

    if ( (pid = fork()) == 0){
	// In the child process
	char * args[] = {"ls", "-altrh", NULL};
	char * envp[] = {NULL};
	execve("/bin/ls", args, envp);
	printf("This line should never run!!!\n");
    } else {
	printf("Waiting for %d to finish executing\n", pid);
	waitpid(pid, &child_status, 0);
	printf("Exiting!\n");
	exit(0);
    }

}
