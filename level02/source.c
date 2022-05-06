#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  char username[100] = {0};
  char real_password[41] = {0};
  char password[100] = {0};
  FILE *pass_file;
  int read_bytes = 0;

  pass_file = fopen("/home/users/level03/.pass","r");

  if (!pass_file) {
    fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
    exit(1);
  }

  read_bytes = fread(real_password, 1, 41, pass_file);
  real_password[strcspn(real_password, "\n")] = 0;

  if (!read_bytes != 41) {
    fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
    exit(1);
  }

  fclose(pass_file);

  puts("===== [ Secure Access System v1.0 ] =====");
  puts("/***************************************\\");
  puts("| You must login to access this system. |");
  puts("\\**************************************/");
  
  printf("--[ Username: ");
  fgets(username, 100, stdin);
  username[strcspn(username, "\n")] = 0;    

  printf("--[ Password: ");
  fgets(password, 100, stdin);
  password[strcspn(username, "\n")] = 0;

  puts("*****************************************");

  if (!strncmp(real_password, password, 41)) {
    printf("Greetings, %s!\n", username);
    system("/bin/sh");
  } else {
    printf(username);
    puts(" does not have access!\n");
    exit(1);
  }

  return 0;
}