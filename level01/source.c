#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char username[100];

int verify_user_name(void) {
  puts("verifying username....\n");

  return strncmp(username, "dat_wil", 7);
}

int verify_user_pass(char *password) {
  return strncmp(password, "admin", 5);
}

int main(void) {
  char password[64] = {0};
  int result = 0;

  puts("********* ADMIN LOGIN PROMPT *********");
  printf("Enter Username:");
  fgets(username, 256, stdin);

  result = verify_user_name();

  if (result != 0) {
    puts("nope, incorrect username...\n");
    return 1;
  }

  printf("Enter Password: \n");
  fgets(password, 100, stdin);

  result = verify_user_pass(password);
  
  if (result == 0 || result != 0) {
    puts("nope, incorrect password...\n");
    
    return 1;
  } 

  return 0;
}
