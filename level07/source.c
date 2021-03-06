#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void clear_stdin(void)
{
	char c = 0;

  while((c = getchar()) != -1) {
    if (c == "\n") {
      break ;
    }
  }
}

unsigned int get_unum(void)
{
	unsigned int input = 0;

	fflush(stdout);
	scanf("%u", input);
	clear_stdin();

	return(input);
}

int store_number(unsigned int *data)
{
  unsigned int input = 0;
  unsigned int index = 0;

  printf(" Number: ");
  input = get_unum();
  printf(" Index: ");
  index = get_unum();

  if(index % 3 == 0 || (input >> 24) == 0xb7)
  {
    printf(" *** ERROR! ***\n");
    printf("   This index is reserved for wil!\n");
    printf(" *** ERROR! ***\n");

    return 1;
  }

  data[index] = input;
  return 0;
}


int read_number(unsigned int *data) {
  unsigned int index = 0;

  printf(" Index: ");
  index = get_unum();

  printf(" Number at data[%u] is %u\n", index, data[index]);

  return 0;
}

int main(int argc, char * argv[], char * envp[]) {
  int res = 0;
  char cmd[20] = {0};
  unsigned int data[100] = {0};

	while(*av)
	{
		memset(*av, 0, strlen(*av) - 1);
		*av++;
	}
	while(*envp)
	{
		memset(*envp, 0, strlen(*envp) - 1);
		*envp++;
	}

  puts(
    "----------------------------------------------------\n"\
    "Welcome to wil\'s crappy number stora ge service!   \n"\
    "----------------------------------------------------\n"\
    "Commands:                                           \n"\
    "    store - store a number into the data storage    \n"\
    "    read  - read a number from the data storage     \n"\
    "    quit  - exit the program                        \n"\
    "----------------------------------------------------\n"\
    "wil has reserved some storage :>                    \n"\
    "----------------------------------------------------\n"
  );

  while(1) {
    printf("Input command: ");
    res = 1;

    fgets(cmd, sizeof(cmd), stdin);
    cmd[strlen(cmd)-1] = '\0';

    if(!strncmp(cmd, "store", 5)) {
      res = store_number(data);
    } else if(!strncmp(cmd, "read", 4)) {
      res = read_number(data);
    } else if(!strncmp(cmd, "quit", 4))
      break;
    }

    if(res) {
      printf(" Failed to do %s command\n", cmd);
    } else {
      printf(" Completed %s command successfully\n", cmd);
    }

    memset(cmd, 0, sizeof(cmd));
  }

  return 0;
}