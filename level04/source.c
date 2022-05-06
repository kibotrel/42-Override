#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <stdbool.h>

int main(void) {
  pid_t child = fork();
  char buffer[128] = {0};
  int status = 0;
  int syscall = 0;

  if (!child) {
    prctl(1, 1);
    ptrace(0, 0, 0, 0);
    puts("Give me some shellcode, k");
    gets(buffer);
  } else {
    while (1) {
      wait(&status);

      if (status & 127) {
        puts("child is exiting...");

				return (0); 
      }

      syscall = ptrace(3, child, 44, 0);

      if (syscall == 11) {
        break;
      }
    }

		puts("no exec() for you");
		kill(child, SIGKILL);
  }

  return 0;
}