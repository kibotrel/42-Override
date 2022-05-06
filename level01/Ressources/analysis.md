# [OS and File security](./security.md)

Once logged on the we are prompted the following message:

```shell
$> checksec --file level01
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX enabled    No PIE          No RPATH   No RUNPATH   level01
```

> Same security as previous level.

# [GDB analysis](./gdb.md)

> Useful data on the binary itself.

# Binary compilation

Use this command to compile [`source.c`](../source.c), reproduction source-code of the given binary.

```shell
 $> gcc -m32 -o level01 source.c
```