---
title: "Signals cannot be queued"
date: 2018-10-22T19:53:11-07:00
draft: true
---

Handling signals can tricky. In particular, never forget that within the context
of a process, only a single signal can be pending — signals cannot be queued.
In other words, if a process is in the middle of handling a `SIGINT` signal, the
process discards any other `SIGINT` while in the middle of processing that first
`SIGINT`.

Let's demonstrate this by writing a very simple program that catches **SIGINT**,
the signal sent when you press down the Ctrl + C on the keyboard, and exits
after processing that signal twice.

```
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define SLEEP_TIME 2
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
    printf("Sleeping for %d seconds", SLEEP_TIME);
    sleep(SLEEP_TIME);
}

int main(int argc, char * argv[])
{
    printf("Hello to this buggy signal handler\n");

    signal(SIGINT, handler);

    while(1){
    }
}
```

```
$ ./signal_bugs 
Hello to this buggy signal handler
^CCaught CTRL+C
signal_count = 0
^CCaught CTRL+C
signal_count = 1
```

```
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define SLEEP_TIME 2
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
    printf("Sleeping for %d seconds", SLEEP_TIME);
    sleep(SLEEP_TIME);
}

int main(int argc, char * argv[])
{
    printf("Hello to this buggy signal handler\n");

    signal(SIGINT, handler);

    while(1){
    }
}
```

```
./signal_bugs 
Hello to this buggy signal handler
^CCaught CTRL+C
signal_count = 0
^C^C^C^C^C^C^CSleeping for 2 secondsCaught CTRL+C
signal_count = 1
```
