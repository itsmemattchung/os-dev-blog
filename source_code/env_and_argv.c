#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
    printf("Command line arguments:\n");

    int i;

    for (i=0; i < argc; i++){
	printf("\targ[%d] = %s\n", i, argv[i]);
    }

    printf("Environment variables:\n");

    int j = 0;

    extern char ** environ;
    while (environ[j] != NULL){
	printf("\tenviron[%d] = %s\n", j, environ[j]);
	j++;
    }

    exit(0);

    
}
