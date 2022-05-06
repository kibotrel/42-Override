# Level00

> For introductory information on this operating system and binary securities, check [here](./analysis.md).

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./gdb.md)). As we can clearly see, after our input is taken, a comparison with **5276** is evaluated. All we have to do to spawn a shell is then to input this number.

```shell
  $> ./level00
  ***********************************
  *            -Level00 -           *
  ***********************************
  Password:5276

  Authenticated!
  $ cat /home/users/level01/.pass
  uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```

So next user credentials pair is `level01:uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL`.

Check [here](../source.c) for reproduction source-code of this binary.