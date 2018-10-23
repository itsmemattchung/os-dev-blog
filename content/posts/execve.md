---
title: "Execve"
date: 2018-10-19T21:55:10-07:00
draft: false
---

In the previous posts, we focused on `fork()` and `wait()`. With those two
system calls alone, we created concurrency — `fork()` created a child process
and `wait()` instructed the kernel to reap the child process, the parent process
not proceeding with executing the next line of code until that the child process
finished. But how can we take advantage of the fact that `fork()` creates a
child process and perhaps run a separate program all together?

That's where `execve()` comes in.

When called within a process, `execve` system calls overwrites the virtual
memory within a process, replacing the stack and variables and so on. Moreover,
the process gets overwritten with the program specified in the argument(s)
passed when calling `execve()`. For example, let's write a simple little program
that forks a subprocess which calls `ls`.

```
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
```

Compiling and running this program yields the following output:

```
$ ./execveing 
Forking a child process from parent pid 28630
Waiting for 28631 to finish executing
total 128
-rw-r--r--   1 mattchung  staff   399B Oct 19 20:32 zombie.c
-rwxr-xr-x   1 mattchung  staff   8.4K Oct 19 20:32 zombie
-rw-r--r--   1 mattchung  staff   252B Oct 19 20:32 forking.c
-rwxr-xr-x   1 mattchung  staff   8.3K Oct 19 20:32 forking
-rw-r--r--   1 mattchung  staff   397B Oct 20 10:01 waiting.c
-rwxr-xr-x   1 mattchung  staff   8.4K Oct 20 10:01 waiting
drwxr-xr-x  17 mattchung  staff   578B Oct 21 13:50 ..
-rw-r--r--   1 mattchung  staff   567B Oct 21 15:29 execveing.c
-rwxr-xr-x   1 mattchung  staff   8.6K Oct 21 15:29 execveing
drwxr-xr-x  10 mattchung  staff   340B Oct 21 15:29 .
Exiting!
```

Pretty neat! Bear in mind to keep the (above) to a minimum, I omitted checking
the exit code when calling `execve()`.


