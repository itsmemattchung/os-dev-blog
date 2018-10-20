#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    int x = 0;

    pid_t pid;

    if ( (pid = fork()) == 0){
        printf("Hey, I'm in the child! x=%i\n", --x);
    }

    printf("Goodbye! x=%i\n", ++x);

    return 0;
}
