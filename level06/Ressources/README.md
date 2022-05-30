# Level06

> For introductory information on this operating system and binary securities, check [here](./analysis.md).

Using [`gdb`](https://linux.die.net/man/1/gdb), we can dig through the binary to understand what's going on (full analysis [here](./gdb.md)). This time we need to crack a password system. We must input a login/serial pair and the login will go through a hashing process that looks like this...

```C
int auth(char *login, unsigned int serial) {
  int hash = (login[3] ^ 4919) + 6221293;

  for(int i = 0; i < len; i++) {
    hash += (login[i] ^ hash) % 1337;
  }

  return (serial != hash);
}
```

> The algorithm was simplified but the core function is here. First, some value is assigned to the final hash, a seed in a way... and then each character of the login string is fed to a binary operation before adding it to the hash current value.

So all we have to do is to create a small script that will compute the hash of any login for us to input into the program and get access to a shell.

```JS
const username = process.argv.at(2)

if (username) {
  let hash = (username.charCodeAt(3) ^ 4919) + 6221293

  for (const character of username) {
    const codePoint = character.charCodeAt()

    if (codePoint < 32 || codePoint > 127 ) {
      process.exit(1)
    }

    hash += (codePoint ^ hash) % 1337
  }

  console.log(`Hash for username ${username} is ${hash}`)
} else {
  process.exit(1)
}
```

We simply choose a login and give it to this script so that it spits out the serial we need to input and we're done!


```shell
  $> ./level06 
  ***********************************
  *               level06           *
  ***********************************
  -> Enter Login: kibotrel
  ***********************************
  ***** NEW ACCOUNT DETECTED ********
  ***********************************
  -> Enter Serial: 6234502
  Authenticated!
  $ cat /home/users/level07/.pass
  GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```
So next user credentials pair is `level07:GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8`.

Check [here](../source.c) for reproduction source-code of this binary.