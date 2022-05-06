# [OS and File security](./security.md)

Once logged on the we are prompted the following message:

```shell
$> checksec --file level0
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   level04
```

> No canaries nor NX this time it should be pretty easy.

# [GDB analysis](./gdb.md)

> Useful data on the binary itself.

# Binary compilation

Use this command to compile [`source.c`](../source.c), reproduction source-code of the given binary.

```shell
 $> gcc -m32 -z execstack -fno-stack-protector -o level04 source.c
```