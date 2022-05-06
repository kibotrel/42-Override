# [OS and File security](./security.md)

Once logged on the we are prompted the following message:

```shell
$> checksec --file level02
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   level02
```

> This time RELRO and NX are disabled meaning we could potentially exploit [Global offset table](https://en.wikipedia.org/wiki/Global_Offset_Table) this time.

# [GDB analysis](./gdb.md)

> Useful data on the binary itself.

# Binary compilation

Use this command to compile [`source.c`](../source.c), reproduction source-code of the given binary.

```shell
 $> gcc -Wl,-z,norelro -fno-stack-protector -z execstack -o level02 source.c
```