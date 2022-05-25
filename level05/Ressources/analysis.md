# [OS and File security](./security.md)

Once logged on the we are prompted the following message:

```shell
$> checksec --file level05
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   level05
```

> No protection at all, it should be easy this time.

# [GDB analysis](./gdb.md)

> Useful data on the binary itself.

# Binary compilation

Use this command to compile [`source.c`](../source.c), reproduction source-code of the given binary.

```shell
 $> gcc -m32 -z,norelro -fno-stack-protector -z execstack -o level05 source.c
```