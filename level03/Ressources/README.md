# Level0

> For introductory information on this operating system and binary securities, check [here](./analysis.md).

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./gdb.md)). After a deep analysis we find out that our input is used as part of a poor cypher process. We start from the string ``Q}|u`sfg~sf{}|a3`` and using a XOR on each character with our input substracted to a secret value (**322424845**) we need to land on `Congratulations!`.

The problem with this is that to know the mask you need to apply on any given character to get its ciphered version is as easy as XORing the base character with its ciphered analog. Since we now the base and the expected output, the question is what does `Q ^ C` equal to?
Q's ASCII code is **81** while C's is **67**.

```shell
  $> python -c "print 81 ^ 67"
  18
  $> python -c "print 322424845 - 18"
  322424827
```

> We substract **18** to the known secret to get what we should input so that the result becomes **18**.

Now that we have our input, last step is to get the password of the next user using the built-in way to spawn a shell.

```shell
  $> ./level03 
  ***********************************
  *               level03         **
  ***********************************
  Password:322424827
  $ cat /home/users/level04/.pass
  kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```

So next user credentials pair is `level04:kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf`.

Check [here](../source.c) for reproduction source-code of this binary.