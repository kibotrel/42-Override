# [OS and File security](./security.md)

Once logged on the we are prompted the following message:

```shell
$> checksec --file level06
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   Canary found      NX enabled    No PIE          No RPATH   No RUNPATH   level06
```

> Canaries are present so, buffer overflow might be harder to perform.

# [GDB analysis](./gdb.md)

> Useful data on the binary itself.

# Binary compilation

Use this command to compile [`source.c`](../source.c), reproduction source-code of the given binary.

```shell
 $> gcc -m32 level06 source.c
```