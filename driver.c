#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "func.h"

//Main Method
//Asks for user input and reads stdin accordingly
int main() {
  while (1) {
    printf("Write a command: ");
    char input[256];
    fgets(input, 256, stdin);
    input[strlen(input)-1] = 0;
    char ** separated = malloc(128 * sizeof(char *));
    separated = separate(input);
    int i = 0;
    while (separated[i]) {
      int c = check(separated[i]);
      if (!c) {
	execute(separated[i]);
      }
      else if (c == 1) {
	redirectout(separated[i]);
      }
      else if (c == 2) {
	redirectin(separated[i]);
      }
      else if (c == 3) {
	executepipe(separated[i]);
      }
      i++;
    }
  }
}
