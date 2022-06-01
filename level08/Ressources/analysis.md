# [OS and File security](./security.md)

Once logged on the we are prompted the following message:

```shell
$> checksec --file level08
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Full RELRO      Canary found      NX disabled   No PIE          No RPATH   No RUNPATH   level08
```

> Full RELRO this time, not GOT overwrite for us on that one.

# [GDB analysis](./gdb.md)

> Useful data on the binary itself.

# Binary compilation

Use this command to compile [`source.c`](../source.c), reproduction source-code of the given binary.

```shell
 $> gcc -z execstack -z relro level08 source.c
```