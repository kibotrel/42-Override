# [OS and File security](./security.md)

Once logged on the we are prompted the following message:

```shell
$> checksec --file level00 
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   No canary found   NX enabled    No PIE          No RPATH   No RUNPATH   level00
```

It gives us some information about how binaries are compiled and what we could or couldn't use as leads to exploit these binaries.

- [RELRO](https://www.redhat.com/en/blog/hardening-elf-binaries-using-relocation-read-only-relro) means **Rel**ocation **R**ead-**O**nly. It is a compiler option that force the linker to resolve all dynamically linked functions at the beginning of the execution and then makes the [Global offset table](https://en.wikipedia.org/wiki/Global_Offset_Table) (GOT) read-only. It is meant to prevent some security weakness induced by the GOT itself.
- [Stack canary](https://www.sans.org/blog/stack-canaries-gingerly-sidestepping-the-cage/) is a way to prevent buffer overflows to be exploitable by putting some value after the buffer itself on the stack and check if it was overriden on function return.
- [NX](https://access.redhat.com/solutions/2936741) is an hardware technology use in processors to prevent execuion of certain types of code.
- [PIE](https://en.wikipedia.org/wiki/Position-independent_code) is a process that will randomize code position in memory at run-time, making exploit harder to perform.
- [`RPATH`](https://en.wikipedia.org/wiki/Rpath#:~:text=In%20computing%2C%20rpath%20designates%20the,(or%20another%20shared%20library).) is a variable used at run-time. It contains a list of hard-coded paths in which the binary could search.
- `RUNPATH` is almost the same as `RPATH`. The difference lies in the order they are searched in. `RPATH` is searched in before [`LD_LIBRARY_PATH`]() while `RUNPATH` is searched in after. The meaning of this is that `RPATH` cannot be changed dynamically with environment variables while `RUNPATH` can.

> So for this one, `Partial RELRO` will prevent us from using buffer overflows on global values to overwrite [Global Offset Table (GOT)](https://en.wikipedia.org/wiki/Global_Offset_Table#:~:text=The%20Global%20Offset%20Table%2C%20or,data%20is%20loaded%20at%20runtime.) by forcing it to come before [Block Starting Symbol (BSS)](https://en.wikipedia.org/wiki/.bss) in memory.

# [GDB analysis](./gdb.md)

> Useful data on the binary itself.

# Binary compilation

Use this command to compile [`source.c`](../source.c), reproduction source-code of the given binary.

```shell
 $> gcc -m32 -o level00 source.c
```