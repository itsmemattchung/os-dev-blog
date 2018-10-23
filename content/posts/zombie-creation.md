---
title: "Let's create some zombies"
date: 2018-10-19T17:37:16-07:00
draft: false
---

When a process runs and issues the `fork()` system call, the kernel makes a copy
of the process. This copy is called a child process. Even more interesting is
that the `fork()` call returns twice, once to each process, each process
continuing executing the next line of code. And under normal circumstances, the
parent process should call the `wait()` or `waitpid()` system call, which
*reaps* the child process, signaling the kernel to remove the child process from
the process table. But what if this doesn't happen? What if the child process
finishes, calling `exit()`, but the parent never issues a `wait()` system call?
Well, this is known as a zombie process and is typically considered a bug that
potentially leads to memory leaks.

So, let's create one!

```
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    pid_t pid;

    printf("Let's create a zombie process\n");

    if ( (pid = fork()) == 0){
        printf("Exiting from child process: %d\n", getpid());
        exit(0);
    }

    printf("Parent pid (%d) living forever ...\n", getpid());

    while(1){
    }

    return 0;
}
```

Running this command, here's what you see on the terminal:

```
 ./zombies 
Let's create a zombie process
Parent pid (5506) living forever ...
Exiting from child process: 5507
```

Let's run `ps` and see what processes are running (related to zombies):

```
# ps waux | grep zombie
root      5506  103  0.1   4208   672 pts/4    R+   01:21   0:07 ./zombies
root      5507  0.0  0.0      0     0 pts/4    Z+   01:21   0:00 [zombies] <defunct>
root      5509  0.0  0.4  12000  2212 pts/5    S+   01:21   0:00 grep --color=auto zombie
```

As you can see from the `ps` output, the child process (with pid 5507) remains
in the process table but is labeled as **defunct** (i.e. zombie).
