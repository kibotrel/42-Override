#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void decrypt(unsigned int mask) {
  int i = -1;
  char password[] = "Q}|u`sfg~sf{}|a3";

  while(++i < 17) {
    password[i] ^= mask;
  }

  if (!strncmp(password, "Congratulations!", 16)) {
    system("/bin/sh");
  } else {
    puts("\nInvalid Password");
  }

}

void test(unsigned int input, unsigned int secret) {
  int result = secret - input;

  if ((res >= 1 && res <= 9) || (res >= 16 && res <= 21)) {
    decrypt(res);
  } else {
    decrypt(rand());
  }
}

int main(void) {
  int input;

  srand(time());
  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");
  printf("Password:");
  scanf("%d", &input);
  test(input, 322424845);

  return 0;
}