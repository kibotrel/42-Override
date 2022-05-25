#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  int i = 0;
  char buffer[100];

  fgets(buffer, 100, stdin);

  for (int i = 0; i < strlen(buffer); i++)
      if (buffer[i] >= 'A' && buffer[i] <= 'Z')
          buffer[i] ^= 32;

  printf(buffer);
  exit(0);
}