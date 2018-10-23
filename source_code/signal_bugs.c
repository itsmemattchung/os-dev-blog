#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int signal_count = 0;

void handler(int sig)
{
    // Calling printf() within signal handler is NOT thread safe!
    printf("Caught CTRL+C\n");
    printf("signal_count = %d\n", signal_count);
    signal_count++;
    if (signal_count >= 2){
	exit(0);
    }
}

int main(int argc, char * argv[])
{
    printf("Hello to this buggy signal handler\n");

    signal(SIGINT, handler);

    while(1){
    }
}
