---
title: "Forking"
date: 2018-10-19T15:09:53-07:00
draft: false
---

Let's play around with `fork()`. This system call creates a copy of the
currently running process, returning twice: once to the parent, once to the
child. Here's an example:

```
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int x = 0;

    pid_t pid;

    // Non-production code: not checking for errors
    if ( (pid = fork()) == 0){
        printf("I'm in the child. x=%i", --x);
    }

    printf("Goodbye. x=%i\n", ++x);
}
```

After compiling and running this program, what are some possible results that
get printed out (to standard output) ?

Well, here are a few examples:

```
I'm in the child. x=-1
Goodbye. x=0
Goodbye. x=1
```

or

```
I'm in the child. x=-1
Goodbye. x=1
Goodbye. x=0
```

or even

```
Goodbye. x=1
I'm in the child. x=-1
Goodbye. x=0
```

This last example is possible because the kernel launched the child process
first. In fact, you cannot guarantee that they parent will execute first (at
least not that I'm aware of).

