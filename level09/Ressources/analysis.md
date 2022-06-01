# [OS and File security](./security.md)

Once logged on the we are prompted the following message:

```shell
$> checksec --file level08
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX enabled    PIE enabled     No RPATH   No RUNPATH   level08
```

> PIE code is enabled for this last level, exploits will be harder...

# [GDB analysis](./gdb.md)

> Useful data on the binary itself.

# Binary compilation

Use this command to compile [`source.c`](../source.c), reproduction source-code of the given binary.

```shell
 $> gcc -pie -fPIE -fno-stack-protector -o level9 level9.c
```