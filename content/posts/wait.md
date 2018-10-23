---
title: "Wait"
date: 2018-10-20T09:56:02-07:00
draft: true
---

As you saw in the previous post (on zombie process), we need the parent process
to signal to the kernel that the child processes can be reaped, cleared from the
process table. And to do this, the parent process must call `wait()`.


