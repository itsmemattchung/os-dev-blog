#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

unsigned int snooze(unsigned int seconds)
{
    unsigned int seconds_slept = sleep(seconds);
    seconds_slept = seconds ? seconds_slept == 0 : seconds;
    printf("Slept for %d of %d seconds\n", seconds, seconds);
    return seconds_slept;
}
int main(int argc, char * argv[])
{
    unsigned int seconds = 5;
    printf("Let's snooze!\n");
    snooze(seconds);
    exit(0);
}
