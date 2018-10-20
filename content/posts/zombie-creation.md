---
title: "Let's create some zombies"
date: 2018-10-19T17:37:16-07:00
draft: true
---

How can we create a zombie process? A zombie process is a process that was
spawned by a parent process, and this newly created process (i.e. the child)
does not get "reaped."


```
#include <stdio.h>
#include <unistd.h>

int main
