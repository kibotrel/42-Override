# GDB analysis

[`gdb`](https://linux.die.net/man/1/gdb) is useful for us to understand how a given binary works.

## Main function

Let's see what this program does...

```gdb
  $> gdb ./level00
  (gdb) disassemble main
    Dump of assembler code for function main:
    0x08048494 <+0>:     push   %ebp
    0x08048495 <+1>:     mov    %esp,%ebp
    0x08048497 <+3>:     and    $0xfffffff0,%esp
    0x0804849a <+6>:     sub    $0x20,%esp
    0x0804849d <+9>:     movl   $0x80485f0,(%esp)
    0x080484a4 <+16>:    call   0x8048390 <puts@plt>
    0x080484a9 <+21>:    movl   $0x8048614,(%esp)
    0x080484b0 <+28>:    call   0x8048390 <puts@plt>
    0x080484b5 <+33>:    movl   $0x80485f0,(%esp)
    0x080484bc <+40>:    call   0x8048390 <puts@plt>
    0x080484c1 <+45>:    mov    $0x804862c,%eax
    0x080484c6 <+50>:    mov    %eax,(%esp)
    0x080484c9 <+53>:    call   0x8048380 <printf@plt>
    0x080484ce <+58>:    mov    $0x8048636,%eax
    0x080484d3 <+63>:    lea    0x1c(%esp),%edx
    0x080484d7 <+67>:    mov    %edx,0x4(%esp)
    0x080484db <+71>:    mov    %eax,(%esp)
    0x080484de <+74>:    call   0x80483d0 <__isoc99_scanf@plt>
    0x080484e3 <+79>:    mov    0x1c(%esp),%eax
    0x080484e7 <+83>:    cmp    $0x149c,%eax
    0x080484ec <+88>:    jne    0x804850d <main+121>
    0x080484ee <+90>:    movl   $0x8048639,(%esp)
    0x080484f5 <+97>:    call   0x8048390 <puts@plt>
    0x080484fa <+102>:   movl   $0x8048649,(%esp)
    0x08048501 <+109>:   call   0x80483a0 <system@plt>
    0x08048506 <+114>:   mov    $0x0,%eax
    0x0804850b <+119>:   jmp    0x804851e <main+138>
    0x0804850d <+121>:   movl   $0x8048651,(%esp)
    0x08048514 <+128>:   call   0x8048390 <puts@plt>
    0x08048519 <+133>:   mov    $0x1,%eax
    0x0804851e <+138>:   leave  
    0x0804851f <+139>:   ret 
  End of assembler dump.
```

> It uses [`puts()`](https://man7.org/linux/man-pages/man3/puts.3.html), [`printf()`](https://man7.org/linux/man-pages/man3/printf.3.html), [`scanf()`](https://man7.org/linux/man-pages/man3/scanf.3.html) and [`system()`](https://man7.org/linux/man-pages/man3/system.3.html).

At some point `scanf()` allows us to input a number, latter compared to **5276**.

# Data

## Strings

```gdb
  0x080484fa <+102>:   movl   $0x8048649,(%esp)

  (gdb) x/s 0x8048649
  0x8048649: "/bin/sh"
```

The string `/bin/sh` is located at address `0x8048649`.