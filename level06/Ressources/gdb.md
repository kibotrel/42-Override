# GDB analysis

[`gdb`](https://linux.die.net/man/1/gdb) is useful for us to understand how a given binary works.

## Main function

Let's see what this program does...

```gdb
  $> gdb ./level06
  (gdb) disassemble main
  Dump of assembler code for function main:
    0x08048879 <+0>:     push   %ebp
    0x0804887a <+1>:     mov    %esp,%ebp
    0x0804887c <+3>:     and    $0xfffffff0,%esp
    0x0804887f <+6>:     sub    $0x50,%esp
    0x08048882 <+9>:     mov    0xc(%ebp),%eax
    0x08048885 <+12>:    mov    %eax,0x1c(%esp)
    0x08048889 <+16>:    mov    %gs:0x14,%eax
    0x0804888f <+22>:    mov    %eax,0x4c(%esp)
    0x08048893 <+26>:    xor    %eax,%eax
    0x08048895 <+28>:    push   %eax
    0x08048896 <+29>:    xor    %eax,%eax
    0x08048898 <+31>:    je     0x804889d <main+36>
    0x0804889a <+33>:    add    $0x4,%esp
    0x0804889d <+36>:    pop    %eax
    0x0804889e <+37>:    movl   $0x8048ad4,(%esp)
    0x080488a5 <+44>:    call   0x8048590 <puts@plt>
    0x080488aa <+49>:    movl   $0x8048af8,(%esp)
    0x080488b1 <+56>:    call   0x8048590 <puts@plt>
    0x080488b6 <+61>:    movl   $0x8048ad4,(%esp)
    0x080488bd <+68>:    call   0x8048590 <puts@plt>
    0x080488c2 <+73>:    mov    $0x8048b08,%eax
    0x080488c7 <+78>:    mov    %eax,(%esp)
    0x080488ca <+81>:    call   0x8048510 <printf@plt>
    0x080488cf <+86>:    mov    0x804a060,%eax
    0x080488d4 <+91>:    mov    %eax,0x8(%esp)
    0x080488d8 <+95>:    movl   $0x20,0x4(%esp)
    0x080488e0 <+103>:   lea    0x2c(%esp),%eax
    0x080488e4 <+107>:   mov    %eax,(%esp)
    0x080488e7 <+110>:   call   0x8048550 <fgets@plt>
    0x080488ec <+115>:   movl   $0x8048ad4,(%esp)
    0x080488f3 <+122>:   call   0x8048590 <puts@plt>
    0x080488f8 <+127>:   movl   $0x8048b1c,(%esp)
    0x080488ff <+134>:   call   0x8048590 <puts@plt>
    0x08048904 <+139>:   movl   $0x8048ad4,(%esp)
    0x0804890b <+146>:   call   0x8048590 <puts@plt>
    0x08048910 <+151>:   mov    $0x8048b40,%eax
    0x08048915 <+156>:   mov    %eax,(%esp)
    0x08048918 <+159>:   call   0x8048510 <printf@plt>
    0x0804891d <+164>:   mov    $0x8048a60,%eax
    0x08048922 <+169>:   lea    0x28(%esp),%edx
    0x08048926 <+173>:   mov    %edx,0x4(%esp)
    0x0804892a <+177>:   mov    %eax,(%esp)
    0x0804892d <+180>:   call   0x80485e0 <__isoc99_scanf@plt>
    0x08048932 <+185>:   mov    0x28(%esp),%eax
    0x08048936 <+189>:   mov    %eax,0x4(%esp)
    0x0804893a <+193>:   lea    0x2c(%esp),%eax
    0x0804893e <+197>:   mov    %eax,(%esp)
    0x08048941 <+200>:   call   0x8048748 <auth>
    0x08048946 <+205>:   test   %eax,%eax
    0x08048948 <+207>:   jne    0x8048969 <main+240>
    0x0804894a <+209>:   movl   $0x8048b52,(%esp)
    0x08048951 <+216>:   call   0x8048590 <puts@plt>
    0x08048956 <+221>:   movl   $0x8048b61,(%esp)
    0x0804895d <+228>:   call   0x80485a0 <system@plt>
    0x08048962 <+233>:   mov    $0x0,%eax
    0x08048967 <+238>:   jmp    0x804896e <main+245>
    0x08048969 <+240>:   mov    $0x1,%eax
    0x0804896e <+245>:   mov    0x4c(%esp),%edx
    0x08048972 <+249>:   xor    %gs:0x14,%edx
    0x08048979 <+256>:   je     0x8048980 <main+263>
    0x0804897b <+258>:   call   0x8048580 <__stack_chk_fail@plt>
    0x08048980 <+263>:   leave  
    0x08048981 <+264>:   ret    
  End of assembler dump.
```

> It uses [`puts()`](https://man7.org/linux/man-pages/man3/puts.3.html), [`printf()`](https://man7.org/linux/man-pages/man3/printf.3.html), [`fgets()`](https://linux.die.net/man/3/fgets), [`scanf()`](https://man7.org/linux/man-pages/man3/scanf.3.html), [`system()`](https://man7.org/linux/man-pages/man3/system.3.html) and a custom `auth()` function.


This program is waiting for two inputs, a login and a serial, fed to a custom `auth()` function. If this function returns **0**, a shell is spawned via `system()`.

## Additional functions

As we saw in `main()` we have another function `auth()`, let's get a closer look into it...

```gdb
  $> gdb ./level06
  (gdb) disassemble auth
  Dump of assembler code for function auth:
    0x08048748 <+0>:     push   %ebp
    0x08048749 <+1>:     mov    %esp,%ebp
    0x0804874b <+3>:     sub    $0x28,%esp
    0x0804874e <+6>:     movl   $0x8048a63,0x4(%esp)
    0x08048756 <+14>:    mov    0x8(%ebp),%eax
    0x08048759 <+17>:    mov    %eax,(%esp)
    0x0804875c <+20>:    call   0x8048520 <strcspn@plt>
    0x08048761 <+25>:    add    0x8(%ebp),%eax
    0x08048764 <+28>:    movb   $0x0,(%eax)
    0x08048767 <+31>:    movl   $0x20,0x4(%esp)
    0x0804876f <+39>:    mov    0x8(%ebp),%eax
    0x08048772 <+42>:    mov    %eax,(%esp)
    0x08048775 <+45>:    call   0x80485d0 <strnlen@plt>
    0x0804877a <+50>:    mov    %eax,-0xc(%ebp)
    0x0804877d <+53>:    push   %eax
    0x0804877e <+54>:    xor    %eax,%eax
    0x08048780 <+56>:    je     0x8048785 <auth+61>
    0x08048782 <+58>:    add    $0x4,%esp
    0x08048785 <+61>:    pop    %eax
    0x08048786 <+62>:    cmpl   $0x5,-0xc(%ebp)
    0x0804878a <+66>:    jg     0x8048796 <auth+78>
    0x0804878c <+68>:    mov    $0x1,%eax
    0x08048791 <+73>:    jmp    0x8048877 <auth+303>
    0x08048796 <+78>:    movl   $0x0,0xc(%esp)
    0x0804879e <+86>:    movl   $0x1,0x8(%esp)
    0x080487a6 <+94>:    movl   $0x0,0x4(%esp)
    0x080487ae <+102>:   movl   $0x0,(%esp)
    0x080487b5 <+109>:   call   0x80485f0 <ptrace@plt>
    0x080487ba <+114>:   cmp    $0xffffffff,%eax
    0x080487bd <+117>:   jne    0x80487ed <auth+165>
    0x080487bf <+119>:   movl   $0x8048a68,(%esp)
    0x080487c6 <+126>:   call   0x8048590 <puts@plt>
    0x080487cb <+131>:   movl   $0x8048a8c,(%esp)
    0x080487d2 <+138>:   call   0x8048590 <puts@plt>
    0x080487d7 <+143>:   movl   $0x8048ab0,(%esp)
    0x080487de <+150>:   call   0x8048590 <puts@plt>
    0x080487e3 <+155>:   mov    $0x1,%eax
    0x080487e8 <+160>:   jmp    0x8048877 <auth+303>
    0x080487ed <+165>:   mov    0x8(%ebp),%eax
    0x080487f0 <+168>:   add    $0x3,%eax
    0x080487f3 <+171>:   movzbl (%eax),%eax
    0x080487f6 <+174>:   movsbl %al,%eax
    0x080487f9 <+177>:   xor    $0x1337,%eax
    0x080487fe <+182>:   add    $0x5eeded,%eax
    0x08048803 <+187>:   mov    %eax,-0x10(%ebp)
    0x08048806 <+190>:   movl   $0x0,-0x14(%ebp)
    0x0804880d <+197>:   jmp    0x804885b <auth+275>
    0x0804880f <+199>:   mov    -0x14(%ebp),%eax
    0x08048812 <+202>:   add    0x8(%ebp),%eax
    0x08048815 <+205>:   movzbl (%eax),%eax
    0x08048818 <+208>:   cmp    $0x1f,%al
    0x0804881a <+210>:   jg     0x8048823 <auth+219>
    0x0804881c <+212>:   mov    $0x1,%eax
    0x08048821 <+217>:   jmp    0x8048877 <auth+303>
    0x08048823 <+219>:   mov    -0x14(%ebp),%eax
    0x08048826 <+222>:   add    0x8(%ebp),%eax
    0x08048829 <+225>:   movzbl (%eax),%eax
    0x0804882c <+228>:   movsbl %al,%eax
    0x0804882f <+231>:   mov    %eax,%ecx
    0x08048831 <+233>:   xor    -0x10(%ebp),%ecx
    0x08048834 <+236>:   mov    $0x88233b2b,%edx
    0x08048839 <+241>:   mov    %ecx,%eax
    0x0804883b <+243>:   mul    %edx
    0x0804883d <+245>:   mov    %ecx,%eax
    0x0804883f <+247>:   sub    %edx,%eax
    0x08048841 <+249>:   shr    %eax
    0x08048843 <+251>:   add    %edx,%eax
    0x08048845 <+253>:   shr    $0xa,%eax
    0x08048848 <+256>:   imul   $0x539,%eax,%eax
    0x0804884e <+262>:   mov    %ecx,%edx
    0x08048850 <+264>:   sub    %eax,%edx
    0x08048852 <+266>:   mov    %edx,%eax
    0x08048854 <+268>:   add    %eax,-0x10(%ebp)
    0x08048857 <+271>:   addl   $0x1,-0x14(%ebp)
    0x0804885b <+275>:   mov    -0x14(%ebp),%eax
    0x0804885e <+278>:   cmp    -0xc(%ebp),%eax
    0x08048861 <+281>:   jl     0x804880f <auth+199>
    0x08048863 <+283>:   mov    0xc(%ebp),%eax
    0x08048866 <+286>:   cmp    -0x10(%ebp),%eax
    0x08048869 <+289>:   je     0x8048872 <auth+298>
    0x0804886b <+291>:   mov    $0x1,%eax
    0x08048870 <+296>:   jmp    0x8048877 <auth+303>
    0x08048872 <+298>:   mov    $0x0,%eax
    0x08048877 <+303>:   leave  
    0x08048878 <+304>:   ret
  End of assembler dump.
```

> It uses [`strcspn()`](https://linux.die.net/man/3/strcspn), [`strnlen()`](https://linux.die.net/man/3/strnlen), [`ptrace()`](https://linux.die.net/man/2/ptrace) and [`puts()`](https://man7.org/linux/man-pages/man3/puts.3.html).

We have some sort of hashing function right there. First we have the seed:

```gdb
  0x080487ed <+165>:   mov    0x8(%ebp),%eax
  0x080487f0 <+168>:   add    $0x3,%eax
  0x080487f3 <+171>:   movzbl (%eax),%eax
  0x080487f6 <+174>:   movsbl %al,%eax
  0x080487f9 <+177>:   xor    $0x1337,%eax
  0x080487fe <+182>:   add    $0x5eeded,%eax
```

> The first four instructions load the fourth character of our input login to register `eax`.

Converted into C code it would look like this...

```C
  int hash = (login[3] ^ 0x1337) + 0x5eeded
```

Then in a loop, on each character of the string we run the following operations:

```gdb
  0x08048829 <+225>:   movzbl (%eax),%eax
  0x0804882c <+228>:   movsbl %al,%eax
  0x0804882f <+231>:   mov    %eax,%ecx
  0x08048831 <+233>:   xor    -0x10(%ebp),%ecx
  ...
  0x08048848 <+256>:   imul   $0x539,%eax,%eax
```

> Moving `eax` value (`hash`) in `ecx` register allow the program to use it as a variable to do other operations such as these ones.

Once again in C code it would be...

```C
  hash += (login[i] ^ hash) % 0x539
```