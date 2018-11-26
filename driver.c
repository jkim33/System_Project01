#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char** separate(char* input) {
  char ** ret = malloc(128 * sizeof(char *));
  int i = 0;
  while(input) {
    ret[i] = strsep(&input, ";");
    i++;
  }
  i = 0;
  while (ret[i]) {
    if (strncmp(ret[i], " ", 1) == 0) {
      ret[i] = &ret[i][1];
    }
    if (strncmp(&ret[i][strlen(ret[i])-1], " ", 1) == 0) {
      ret[i][strlen(ret[i])-1] = 0;
    }
    i++;
  }
  return ret;
}

void changedir(char* input) {
  int f = fork();
  if (f) {
    int status;
    wait(&status);
  }
  else {
    chdir(input);
  }
  return;
}

void execute(char* input) {
  if (strncmp(input, "cd", 2) == 0) {
    char* new = &input[3];
    changedir(new);
    return;
  }
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
  }
  return;
}

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
      execute(separated[i]);
      i++;
    }
  }
}
