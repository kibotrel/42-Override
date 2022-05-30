#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>
#include <unistd.h>

int auth(char *username, unsigned int serial){
  int len;
  unsigned int hash;

  username[strcspn(username, "\n")] = 0;
  len = strnlen(username, 32);

  if (len < 6) {
    return 1;
  }

  if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
  {
    puts("\x1b[32m.---------------------------.");
    puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
    puts("\x1b[32m\'---------------------------\'");

    return 1;
  }

  hash = (username[3] ^ 4919) + 6221293;

  for(int i = 0; i < len; i++) {
    if (username[i] < 32 || username[i] > 127) {
      return 1;
    }

    hash += (username[i] ^ hash) % 1337;
  }

  return (serial != hash)
}

int main(void){
  unsigned int serial;
  char username[32];

  puts("***********************************");
  puts("*\t\tlevel06\t\t  *");
  puts("***********************************");
  printf("-> Enter Login: ");
  fgets(username, 32, stdin);
  puts("***********************************");
  puts("***** NEW ACCOUNT DETECTED ********");
  puts("***********************************");
  puts("-> Enter Serial: ");
  scanf("%u", &serial);

  if (!auth(username, serial)) {
    puts("Authenticated!");
    system("/bin/sh");
    return 0;
  }
  return 1;
}