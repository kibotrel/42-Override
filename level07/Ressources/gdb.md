# GDB analysis

[`gdb`](https://linux.die.net/man/1/gdb) is useful for us to understand how a given binary works.

## Main function

Let's see what this program does...

```gdb
  $> gdb ./level07
  (gdb) disassemble main
  Dump of assembler code for function main:
    0x08048723 <+0>:     push   %ebp
    0x08048724 <+1>:     mov    %esp,%ebp
    0x08048726 <+3>:     push   %edi
    0x08048727 <+4>:     push   %esi
    0x08048728 <+5>:     push   %ebx
    0x08048729 <+6>:     and    $0xfffffff0,%esp
    0x0804872c <+9>:     sub    $0x1d0,%esp
    0x08048732 <+15>:    mov    0xc(%ebp),%eax
    0x08048735 <+18>:    mov    %eax,0x1c(%esp)
    0x08048739 <+22>:    mov    0x10(%ebp),%eax
    0x0804873c <+25>:    mov    %eax,0x18(%esp)
    0x08048740 <+29>:    mov    %gs:0x14,%eax
    0x08048746 <+35>:    mov    %eax,0x1cc(%esp)
    0x0804874d <+42>:    xor    %eax,%eax
    0x0804874f <+44>:    movl   $0x0,0x1b4(%esp)
    0x0804875a <+55>:    movl   $0x0,0x1b8(%esp)
    0x08048765 <+66>:    movl   $0x0,0x1bc(%esp)
    0x08048770 <+77>:    movl   $0x0,0x1c0(%esp)
    0x0804877b <+88>:    movl   $0x0,0x1c4(%esp)
    0x08048786 <+99>:    movl   $0x0,0x1c8(%esp)
    0x08048791 <+110>:   lea    0x24(%esp),%ebx
    0x08048795 <+114>:   mov    $0x0,%eax
    0x0804879a <+119>:   mov    $0x64,%edx
    0x0804879f <+124>:   mov    %ebx,%edi
    0x080487a1 <+126>:   mov    %edx,%ecx
    0x080487a3 <+128>:   rep stos %eax,%es:(%edi)
    0x080487a5 <+130>:   jmp    0x80487ea <main+199>
    0x080487a7 <+132>:   mov    0x1c(%esp),%eax
    0x080487ab <+136>:   mov    (%eax),%eax
    0x080487ad <+138>:   movl   $0xffffffff,0x14(%esp)
    0x080487b5 <+146>:   mov    %eax,%edx
    0x080487b7 <+148>:   mov    $0x0,%eax
    0x080487bc <+153>:   mov    0x14(%esp),%ecx
    0x080487c0 <+157>:   mov    %edx,%edi
    0x080487c2 <+159>:   repnz scas %es:(%edi),%al
    0x080487c4 <+161>:   mov    %ecx,%eax
    0x080487c6 <+163>:   not    %eax
    0x080487c8 <+165>:   lea    -0x1(%eax),%edx
    0x080487cb <+168>:   mov    0x1c(%esp),%eax
    0x080487cf <+172>:   mov    (%eax),%eax
    0x080487d1 <+174>:   mov    %edx,0x8(%esp)
    0x080487d5 <+178>:   movl   $0x0,0x4(%esp)
    0x080487dd <+186>:   mov    %eax,(%esp)
    0x080487e0 <+189>:   call   0x80484f0 <memset@plt>
    0x080487e5 <+194>:   addl   $0x4,0x1c(%esp)
    0x080487ea <+199>:   mov    0x1c(%esp),%eax
    0x080487ee <+203>:   mov    (%eax),%eax
    0x080487f0 <+205>:   test   %eax,%eax
    0x080487f2 <+207>:   jne    0x80487a7 <main+132>
    0x080487f4 <+209>:   jmp    0x8048839 <main+278>
    0x080487f6 <+211>:   mov    0x18(%esp),%eax
    0x080487fa <+215>:   mov    (%eax),%eax
    0x080487fc <+217>:   movl   $0xffffffff,0x14(%esp)
    0x08048804 <+225>:   mov    %eax,%edx
    0x08048806 <+227>:   mov    $0x0,%eax
    0x0804880b <+232>:   mov    0x14(%esp),%ecx
    0x0804880f <+236>:   mov    %edx,%edi
    0x08048811 <+238>:   repnz scas %es:(%edi),%al
    0x08048813 <+240>:   mov    %ecx,%eax
    0x08048815 <+242>:   not    %eax
    0x08048817 <+244>:   lea    -0x1(%eax),%edx
    0x0804881a <+247>:   mov    0x18(%esp),%eax
    0x0804881e <+251>:   mov    (%eax),%eax
    0x08048820 <+253>:   mov    %edx,0x8(%esp)
    0x08048824 <+257>:   movl   $0x0,0x4(%esp)
    0x0804882c <+265>:   mov    %eax,(%esp)
    0x0804882f <+268>:   call   0x80484f0 <memset@plt>
    0x08048834 <+273>:   addl   $0x4,0x18(%esp)
    0x08048839 <+278>:   mov    0x18(%esp),%eax
    0x0804883d <+282>:   mov    (%eax),%eax
    0x0804883f <+284>:   test   %eax,%eax
    0x08048841 <+286>:   jne    0x80487f6 <main+211>
    0x08048843 <+288>:   movl   $0x8048b38,(%esp)
    0x0804884a <+295>:   call   0x80484c0 <puts@plt>
    0x0804884f <+300>:   mov    $0x8048d4b,%eax
    0x08048854 <+305>:   mov    %eax,(%esp)
    0x08048857 <+308>:   call   0x8048470 <printf@plt>
    0x0804885c <+313>:   movl   $0x1,0x1b4(%esp)
    0x08048867 <+324>:   mov    0x804a040,%eax
    0x0804886c <+329>:   mov    %eax,0x8(%esp)
    0x08048870 <+333>:   movl   $0x14,0x4(%esp)
    0x08048878 <+341>:   lea    0x1b8(%esp),%eax
    0x0804887f <+348>:   mov    %eax,(%esp)
    0x08048882 <+351>:   call   0x80484a0 <fgets@plt>
    0x08048887 <+356>:   lea    0x1b8(%esp),%eax
    0x0804888e <+363>:   movl   $0xffffffff,0x14(%esp)
    0x08048896 <+371>:   mov    %eax,%edx
    0x08048898 <+373>:   mov    $0x0,%eax
    0x0804889d <+378>:   mov    0x14(%esp),%ecx
    0x080488a1 <+382>:   mov    %edx,%edi
    0x080488a3 <+384>:   repnz scas %es:(%edi),%al
    0x080488a5 <+386>:   mov    %ecx,%eax
    0x080488a7 <+388>:   not    %eax
    0x080488a9 <+390>:   sub    $0x1,%eax
    0x080488ac <+393>:   sub    $0x1,%eax
    0x080488af <+396>:   movb   $0x0,0x1b8(%esp,%eax,1)
    0x080488b7 <+404>:   lea    0x1b8(%esp),%eax
    0x080488be <+411>:   mov    %eax,%edx
    0x080488c0 <+413>:   mov    $0x8048d5b,%eax
    0x080488c5 <+418>:   mov    $0x5,%ecx
    0x080488ca <+423>:   mov    %edx,%esi
    0x080488cc <+425>:   mov    %eax,%edi
    0x080488ce <+427>:   repz cmpsb %es:(%edi),%ds:(%esi)
    0x080488d0 <+429>:   seta   %dl
    0x080488d3 <+432>:   setb   %al
    0x080488d6 <+435>:   mov    %edx,%ecx
    0x080488d8 <+437>:   sub    %al,%cl
    0x080488da <+439>:   mov    %ecx,%eax
    0x080488dc <+441>:   movsbl %al,%eax
    0x080488df <+444>:   test   %eax,%eax
    0x080488e1 <+446>:   jne    0x80488f8 <main+469>
    0x080488e3 <+448>:   lea    0x24(%esp),%eax
    0x080488e7 <+452>:   mov    %eax,(%esp)
    0x080488ea <+455>:   call   0x8048630 <store_number>
    0x080488ef <+460>:   mov    %eax,0x1b4(%esp)
    0x080488f6 <+467>:   jmp    0x8048965 <main+578>
    0x080488f8 <+469>:   lea    0x1b8(%esp),%eax
    0x080488ff <+476>:   mov    %eax,%edx
    0x08048901 <+478>:   mov    $0x8048d61,%eax
    0x08048906 <+483>:   mov    $0x4,%ecx
    0x0804890b <+488>:   mov    %edx,%esi
    0x0804890d <+490>:   mov    %eax,%edi
    0x0804890f <+492>:   repz cmpsb %es:(%edi),%ds:(%esi)
    0x08048911 <+494>:   seta   %dl
    0x08048914 <+497>:   setb   %al
    0x08048917 <+500>:   mov    %edx,%ecx
    0x08048919 <+502>:   sub    %al,%cl
    0x0804891b <+504>:   mov    %ecx,%eax
    0x0804891d <+506>:   movsbl %al,%eax
    0x08048920 <+509>:   test   %eax,%eax
    0x08048922 <+511>:   jne    0x8048939 <main+534>
    0x08048924 <+513>:   lea    0x24(%esp),%eax
    0x08048928 <+517>:   mov    %eax,(%esp)
    0x0804892b <+520>:   call   0x80486d7 <read_number>
    0x08048930 <+525>:   mov    %eax,0x1b4(%esp)
    0x08048937 <+532>:   jmp    0x8048965 <main+578>
    0x08048939 <+534>:   lea    0x1b8(%esp),%eax
    0x08048940 <+541>:   mov    %eax,%edx
    0x08048942 <+543>:   mov    $0x8048d66,%eax
    0x08048947 <+548>:   mov    $0x4,%ecx
    0x0804894c <+553>:   mov    %edx,%esi
    0x0804894e <+555>:   mov    %eax,%edi
    0x08048950 <+557>:   repz cmpsb %es:(%edi),%ds:(%esi)
    0x08048952 <+559>:   seta   %dl
    0x08048955 <+562>:   setb   %al
    0x08048958 <+565>:   mov    %edx,%ecx
    0x0804895a <+567>:   sub    %al,%cl
    0x0804895c <+569>:   mov    %ecx,%eax
    0x0804895e <+571>:   movsbl %al,%eax
    0x08048961 <+574>:   test   %eax,%eax
    0x08048963 <+576>:   je     0x80489cf <main+684>
    0x08048965 <+578>:   cmpl   $0x0,0x1b4(%esp)
    0x0804896d <+586>:   je     0x8048989 <main+614>
    0x0804896f <+588>:   mov    $0x8048d6b,%eax
    0x08048974 <+593>:   lea    0x1b8(%esp),%edx
    0x0804897b <+600>:   mov    %edx,0x4(%esp)
    0x0804897f <+604>:   mov    %eax,(%esp)
    0x08048982 <+607>:   call   0x8048470 <printf@plt>
    0x08048987 <+612>:   jmp    0x80489a1 <main+638>
    0x08048989 <+614>:   mov    $0x8048d88,%eax
    0x0804898e <+619>:   lea    0x1b8(%esp),%edx
    0x08048995 <+626>:   mov    %edx,0x4(%esp)
    0x08048999 <+630>:   mov    %eax,(%esp)
    0x0804899c <+633>:   call   0x8048470 <printf@plt>
    0x080489a1 <+638>:   lea    0x1b8(%esp),%eax
    0x080489a8 <+645>:   movl   $0x0,(%eax)
    0x080489ae <+651>:   movl   $0x0,0x4(%eax)
    0x080489b5 <+658>:   movl   $0x0,0x8(%eax)
    0x080489bc <+665>:   movl   $0x0,0xc(%eax)
    0x080489c3 <+672>:   movl   $0x0,0x10(%eax)
    0x080489ca <+679>:   jmp    0x804884f <main+300>
    0x080489cf <+684>:   nop
    0x080489d0 <+685>:   mov    $0x0,%eax
    0x080489d5 <+690>:   mov    0x1cc(%esp),%esi
    0x080489dc <+697>:   xor    %gs:0x14,%esi
    0x080489e3 <+704>:   je     0x80489ea <main+711>
    0x080489e5 <+706>:   call   0x80484b0 <__stack_chk_fail@plt>
    0x080489ea <+711>:   lea    -0xc(%ebp),%esp
    0x080489ed <+714>:   pop    %ebx
    0x080489ee <+715>:   pop    %esi
    0x080489ef <+716>:   pop    %edi
    0x080489f0 <+717>:   pop    %ebp
    0x080489f1 <+718>:   ret    
  End of assembler dump.
```

> It uses [`memset()`](https://man7.org/linux/man-pages/man3/memset.3.html), [`puts()`](https://man7.org/linux/man-pages/man3/puts.3.html), [`printf()`](https://man7.org/linux/man-pages/man3/printf.3.html), [`fgets()`](https://linux.die.net/man/3/fgets) and two custom functions `store_number()` and `read_number()`.

First, this program is erasing the environment variables along with the array of program's arguments. So we probably can't perform a shellcode injection this time. Then it displays us a little interface with few commands:

- `store` allows us to store some data in the store.
- `read` allows us to read some data from the store.
- `quit` leaves the infinite loop and quit the program.

What the program call "storage" is a simple array of **100** integers that we can fill with whatever we want.

```gdb
  0x0804879a <+119>:   mov    $0x64,%edx
```

> This line at the beginning of `main()` tells us the size of our buffer. `0x64` = **100**.

## Additional functions

Let's see how `store_number()` behaves...

```gdb
  $> gdb ./level07
  (gdb) disassemble store_number
  Dump of assembler code for function store_number:
    0x08048630 <+0>:     push   %ebp
    0x08048631 <+1>:     mov    %esp,%ebp
    0x08048633 <+3>:     sub    $0x28,%esp
    0x08048636 <+6>:     movl   $0x0,-0x10(%ebp)
    0x0804863d <+13>:    movl   $0x0,-0xc(%ebp)
    0x08048644 <+20>:    mov    $0x8048ad3,%eax
    0x08048649 <+25>:    mov    %eax,(%esp)
    0x0804864c <+28>:    call   0x8048470 <printf@plt>
    0x08048651 <+33>:    call   0x80485e7 <get_unum>
    0x08048656 <+38>:    mov    %eax,-0x10(%ebp)
    0x08048659 <+41>:    mov    $0x8048add,%eax
    0x0804865e <+46>:    mov    %eax,(%esp)
    0x08048661 <+49>:    call   0x8048470 <printf@plt>
    0x08048666 <+54>:    call   0x80485e7 <get_unum>
    0x0804866b <+59>:    mov    %eax,-0xc(%ebp)
    0x0804866e <+62>:    mov    -0xc(%ebp),%ecx
    0x08048671 <+65>:    mov    $0xaaaaaaab,%edx
    0x08048676 <+70>:    mov    %ecx,%eax
    0x08048678 <+72>:    mul    %edx
    0x0804867a <+74>:    shr    %edx
    0x0804867c <+76>:    mov    %edx,%eax
    0x0804867e <+78>:    add    %eax,%eax
    0x08048680 <+80>:    add    %edx,%eax
    0x08048682 <+82>:    mov    %ecx,%edx
    0x08048684 <+84>:    sub    %eax,%edx
    0x08048686 <+86>:    test   %edx,%edx
    0x08048688 <+88>:    je     0x8048697 <store_number+103>
    0x0804868a <+90>:    mov    -0x10(%ebp),%eax
    0x0804868d <+93>:    shr    $0x18,%eax
    0x08048690 <+96>:    cmp    $0xb7,%eax
    0x08048695 <+101>:   jne    0x80486c2 <store_number+146>
    0x08048697 <+103>:   movl   $0x8048ae6,(%esp)
    0x0804869e <+110>:   call   0x80484c0 <puts@plt>
    0x080486a3 <+115>:   movl   $0x8048af8,(%esp)
    0x080486aa <+122>:   call   0x80484c0 <puts@plt>
    0x080486af <+127>:   movl   $0x8048ae6,(%esp)
    0x080486b6 <+134>:   call   0x80484c0 <puts@plt>
    0x080486bb <+139>:   mov    $0x1,%eax
    0x080486c0 <+144>:   jmp    0x80486d5 <store_number+165>
    0x080486c2 <+146>:   mov    -0xc(%ebp),%eax
    0x080486c5 <+149>:   shl    $0x2,%eax
    0x080486c8 <+152>:   add    0x8(%ebp),%eax
    0x080486cb <+155>:   mov    -0x10(%ebp),%edx
    0x080486ce <+158>:   mov    %edx,(%eax)
    0x080486d0 <+160>:   mov    $0x0,%eax
    0x080486d5 <+165>:   leave  
    0x080486d6 <+166>:   ret
  End of assembler dump.
```

> It uses [`printf()`](https://man7.org/linux/man-pages/man3/printf.3.html), [`puts()`](https://man7.org/linux/man-pages/man3/puts.3.html) and a custom function `get_unum()`.

This function asks which value to store at which index of the array with a little twist according to Ghidra's feedback...

```C
  (index % 3 == 0 || (input >> 24) == 0xb7) {
    printf(" *** ERROR! ***\n");
    printf("   This index is reserved for wil!\n");
    printf(" *** ERROR! ***\n");

    return 1;
  }
```

> The requested index can't be a multiple of **3** and its first byte can't be `0xb7`, representing the range of libc call addresses.

# Data

## Strings

```gdb
  (gdb) find &system, +999999999, "/bin/sh"
  0xf7f897ec
```

The string `/bin/sh` is located at address `0xf7f897ec`.

## Function addresses

```gdb
  (gdb) print &system
  $1 = (<text variable, no debug info> *) 0xf7e6aed0 <system>
```

Function `system()` is located at address `0xf7e6aed0`.

```gdb
  (gdb) print &exit
  $1 = (<text variable, no debug info> *) 0xf7e5eb70 <system>
```

Function `exit()` is located at address `0xf7e5eb70`.

## Buffer offset

Since we'll need to create a buffer overflow, we must retrieve its offset, for that easiest way is to break before `store_number()` or `read_number()` and get both EIP's value and buffer's address to substract them.

```gdb
  (gdb) b *main+520
  Breakpoint 1 at 0x804892b
  (gdb) run
  Starting program: /home/users/level07/level07 
  ----------------------------------------------------
    Welcome to wil's crappy number storage service!   
  ----------------------------------------------------
  Commands:                                          
      store - store a number into the data storage    
      read  - read a number from the data storage     
      quit  - exit the program                        
  ----------------------------------------------------
    wil has reserved some storage :>                 
  ----------------------------------------------------

  Input command: read

  Breakpoint 1, 0x0804892b in main ()
  (gdb) i r
  eax            0xffffd544       -10940
  ecx            0xffffd600       -10752
  edx            0xffffd600       -10752
  ebx            0xffffd544       -10940
  esp            0xffffd520       0xffffd520
  ebp            0xffffd708       0xffffd708
  esi            0xffffd6dc       -10532
  edi            0x8048d65        134516069
  eip            0x804892b        0x804892b <main+520>
  eflags         0x246    [ PF ZF IF ]
  cs             0x23     35
  ss             0x2b     43
  ds             0x2b     43
  es             0x2b     43
  fs             0x0      0
  gs             0x63     99
  (gdb) i f
  Stack level 0, frame at 0xffffd710:
  eip = 0x804892b in main; saved eip 0xf7e45513
  Arglist at 0xffffd708, args: 
  Locals at 0xffffd708, Previous frame's sp is 0xffffd710
  Saved registers:
    ebx at 0xffffd6fc, ebp at 0xffffd708, esi at 0xffffd700, edi at 0xffffd704, eip at 0xffffd70c
  (gdb) print 0xffffd70c - 0xffffd544
  $1 = 456
```

> Since our buffer is the only parameter of the function, it is stored in `eax` register.

So the offset of this buffer is **456** bytes.