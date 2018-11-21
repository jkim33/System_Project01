#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void execute(char* input) {
  char ** args = malloc(256 * sizeof(char *));
  int i = 0;
  while(input) {
    args[i] = strsep(&input, " ");
    i++;
  }
  int f = fork();
  if (f) {
    int status;
    wait(&status);
  }
  else {
    execvp(args[0], args);
    return;
  }
  return;
}

int main() {
  while (1) {
    printf("Input: ");
    char input[256];
    fgets(input, 256, stdin);
    input[strlen(input)-1] = 0;
    execute(input);
  }
}
