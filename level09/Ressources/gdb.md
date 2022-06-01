# GDB analysis

[`gdb`](https://linux.die.net/man/1/gdb) is useful for us to understand how a given binary works.

## Main function

Let's see what this program does...

```gdb
  $> gdb ./level09
  (gdb) disassemble main
  Dump of assembler code for function main:
    0x0000000000000aa8 <+0>:     push   %rbp
    0x0000000000000aa9 <+1>:     mov    %rsp,%rbp
    0x0000000000000aac <+4>:     lea    0x15d(%rip),%rdi        # 0xc10
    0x0000000000000ab3 <+11>:    callq  0x730 <puts@plt>
    0x0000000000000ab8 <+16>:    callq  0x8c0 <handle_msg>
    0x0000000000000abd <+21>:    mov    $0x0,%eax
    0x0000000000000ac2 <+26>:    pop    %rbp
    0x0000000000000ac3 <+27>:    retq   
  End of assembler dump.
```

> It uses [`puts()`](https://man7.org/linux/man-pages/man3/puts.3.html) and a custom function `handle_msg()`.

Nothing really interesting here, this `main()` probably has all of its logic within `handle_msg()`.

## Additional functions

Since nothing useful was in `main()`, maybe disassembling `handle_msg()` would help us to understand what's happening.

```gdb
  $> gdb ./level09
  (gdb) disassemble handle_msg
  Dump of assembler code for function handle_msg:
    0x00000000000008c0 <+0>:     push   %rbp
    0x00000000000008c1 <+1>:     mov    %rsp,%rbp
    0x00000000000008c4 <+4>:     sub    $0xc0,%rsp
    0x00000000000008cb <+11>:    lea    -0xc0(%rbp),%rax
    0x00000000000008d2 <+18>:    add    $0x8c,%rax
    0x00000000000008d8 <+24>:    movq   $0x0,(%rax)
    0x00000000000008df <+31>:    movq   $0x0,0x8(%rax)
    0x00000000000008e7 <+39>:    movq   $0x0,0x10(%rax)
    0x00000000000008ef <+47>:    movq   $0x0,0x18(%rax)
    0x00000000000008f7 <+55>:    movq   $0x0,0x20(%rax)
    0x00000000000008ff <+63>:    movl   $0x8c,-0xc(%rbp)
    0x0000000000000906 <+70>:    lea    -0xc0(%rbp),%rax
    0x000000000000090d <+77>:    mov    %rax,%rdi
    0x0000000000000910 <+80>:    callq  0x9cd <set_username>
    0x0000000000000915 <+85>:    lea    -0xc0(%rbp),%rax
    0x000000000000091c <+92>:    mov    %rax,%rdi
    0x000000000000091f <+95>:    callq  0x932 <set_msg>
    0x0000000000000924 <+100>:   lea    0x295(%rip),%rdi        # 0xbc0
    0x000000000000092b <+107>:   callq  0x730 <puts@plt>
    0x0000000000000930 <+112>:   leaveq 
    0x0000000000000931 <+113>:   retq  
  End of assembler dump.
```

> It uses [`puts()`](https://man7.org/linux/man-pages/man3/puts.3.html) and two custom functions `set_username()` and `set_msg()`.

Once again nothing really interesting beside what looks like a structure decleration. Move on `set_username()`...

```gdb
  $> gdb ./level09
  (gdb) disassemble set_username
  Dump of assembler code for function set_username:
    0x00000000000009cd <+0>:     push   %rbp
    0x00000000000009ce <+1>:     mov    %rsp,%rbp
    0x00000000000009d1 <+4>:     sub    $0xa0,%rsp
    0x00000000000009d8 <+11>:    mov    %rdi,-0x98(%rbp)
    0x00000000000009df <+18>:    lea    -0x90(%rbp),%rax
    0x00000000000009e6 <+25>:    mov    %rax,%rsi
    0x00000000000009e9 <+28>:    mov    $0x0,%eax
    0x00000000000009ee <+33>:    mov    $0x10,%edx
    0x00000000000009f3 <+38>:    mov    %rsi,%rdi
    0x00000000000009f6 <+41>:    mov    %rdx,%rcx
    0x00000000000009f9 <+44>:    rep stos %rax,%es:(%rdi)
    0x00000000000009fc <+47>:    lea    0x1e1(%rip),%rdi        # 0xbe4
    0x0000000000000a03 <+54>:    callq  0x730 <puts@plt>
    0x0000000000000a08 <+59>:    lea    0x1d0(%rip),%rax        # 0xbdf
    0x0000000000000a0f <+66>:    mov    %rax,%rdi
    0x0000000000000a12 <+69>:    mov    $0x0,%eax
    0x0000000000000a17 <+74>:    callq  0x750 <printf@plt>
    0x0000000000000a1c <+79>:    mov    0x201595(%rip),%rax        # 0x201fb8
    0x0000000000000a23 <+86>:    mov    (%rax),%rax
    0x0000000000000a26 <+89>:    mov    %rax,%rdx
    0x0000000000000a29 <+92>:    lea    -0x90(%rbp),%rax
    0x0000000000000a30 <+99>:    mov    $0x80,%esi
    0x0000000000000a35 <+104>:   mov    %rax,%rdi
    0x0000000000000a38 <+107>:   callq  0x770 <fgets@plt>
    0x0000000000000a3d <+112>:   movl   $0x0,-0x4(%rbp)
    0x0000000000000a44 <+119>:   jmp    0xa6a <set_username+157>
    0x0000000000000a46 <+121>:   mov    -0x4(%rbp),%eax
    0x0000000000000a49 <+124>:   cltq   
    0x0000000000000a4b <+126>:   movzbl -0x90(%rbp,%rax,1),%ecx
    0x0000000000000a53 <+134>:   mov    -0x98(%rbp),%rdx
    0x0000000000000a5a <+141>:   mov    -0x4(%rbp),%eax
    0x0000000000000a5d <+144>:   cltq   
    0x0000000000000a5f <+146>:   mov    %cl,0x8c(%rdx,%rax,1)
    0x0000000000000a66 <+153>:   addl   $0x1,-0x4(%rbp)
    0x0000000000000a6a <+157>:   cmpl   $0x28,-0x4(%rbp)
    0x0000000000000a6e <+161>:   jg     0xa81 <set_username+180>
    0x0000000000000a70 <+163>:   mov    -0x4(%rbp),%eax
    0x0000000000000a73 <+166>:   cltq   
    0x0000000000000a75 <+168>:   movzbl -0x90(%rbp,%rax,1),%eax
    0x0000000000000a7d <+176>:   test   %al,%al
    0x0000000000000a7f <+178>:   jne    0xa46 <set_username+121>
    0x0000000000000a81 <+180>:   mov    -0x98(%rbp),%rax
    0x0000000000000a88 <+187>:   lea    0x8c(%rax),%rdx
    0x0000000000000a8f <+194>:   lea    0x165(%rip),%rax        # 0xbfb
    0x0000000000000a96 <+201>:   mov    %rdx,%rsi
    0x0000000000000a99 <+204>:   mov    %rax,%rdi
    0x0000000000000a9c <+207>:   mov    $0x0,%eax
    0x0000000000000aa1 <+212>:   callq  0x750 <printf@plt>
    0x0000000000000aa6 <+217>:   leaveq 
    0x0000000000000aa7 <+218>:   retq   
  End of assembler dump.
```
> 

We finaly find something interesting in the following snippet:

```gdb
  0x0000000000000a46 <+121>:   mov    -0x4(%rbp),%eax
  0x0000000000000a49 <+124>:   cltq   
  0x0000000000000a4b <+126>:   movzbl -0x90(%rbp,%rax,1),%ecx
  0x0000000000000a53 <+134>:   mov    -0x98(%rbp),%rdx
  0x0000000000000a5a <+141>:   mov    -0x4(%rbp),%eax
  0x0000000000000a5d <+144>:   cltq   
  0x0000000000000a5f <+146>:   mov    %cl,0x8c(%rdx,%rax,1)
  0x0000000000000a66 <+153>:   addl   $0x1,-0x4(%rbp)
  0x0000000000000a6a <+157>:   cmpl   $0x28,-0x4(%rbp)
  0x0000000000000a6e <+161>:   jg     0xa81 <set_username+180>
  0x0000000000000a70 <+163>:   mov    -0x4(%rbp),%eax
  0x0000000000000a73 <+166>:   cltq   
  0x0000000000000a75 <+168>:   movzbl -0x90(%rbp,%rax,1),%eax
  0x0000000000000a7d <+176>:   test   %al,%al
  0x0000000000000a7f <+178>:   jne    0xa46 <set_username+121>
```

> This is a loop that copies data from one place to another while some variable is less than **41**.
