# [OS and File security](./security.md)

Once logged on the we are prompted the following message:

```shell
$> checksec --file level03
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   Canary found      NX enabled    No PIE          No RPATH   No RUNPATH   level03
```

> This time canaries are used to protect the binary, might be a bit harder.

# [GDB analysis](./gdb.md)

> Useful data on the binary itself.

# Binary compilation

Use this command to compile [`source.c`](../source.c), reproduction source-code of the given binary.

```shell
 $> gcc -o level0 source.c
```