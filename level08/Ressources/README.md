# Level08

> For introductory information on this operating system and binary securities, check [here](./analysis.md).

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./gdb.md)). This time a simple reverse engineering will do the job perfectly. We are given a program that is basically copy-pasting file content into a `backups/` folder.

To perform this process, the program checks for a `.log` located at the root of `backups/` to track every action and if a path that matches our input is found in its arborescence. If those two conditions are met, then the program copies the content from the input to the "backup" file.

So all we have to do is asking the program to copies the content from `/home/users/level09/.pass` to get the next password but since we do not have permission to create any file in `backups/` we'll reproduce this file-tree in `/tmp/`.


```shell
  $> cd /tmp/ ; mkdir -p backups/home/users/level09 ; touch backups/.log
  $> ~/level08 /home/users/level09/.pass && cat backups/home/users/level09/.pass 
  fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```

So next user credentials pair is `level09:fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S`.

Check [here](../source.c) for reproduction source-code of this binary.