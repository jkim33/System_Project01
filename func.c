#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "func.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input: char *

Utilizes strsep to detect and split a string by semicolons and removes whitespaces
Returns an array of executable strings

Output: char **
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input: char *
Takes in a string of executables
Separates the string by either a ">", ">", or "|"

Outputs an array of executable terminal calls
Output: char **
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
char** separateinput(char *input) {
  char ** ret = malloc(2 * sizeof(char *));
  int i = 0;
  while(input) {
    ret[i] = strsep(&input, "><|");
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input: char *
Forks and changes the directory to the input value

Returns a void as we are only modifying the directory
Output: returns void
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input: char *

Executes all executable strings that don't involve a redirect or a pipe
Forks and executes based on the string

Output: void
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input: char *

Redirects the first input into 2nd file, overwrites

Output: void
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void redirectout(char *input) {
  char** separated = malloc(2 * sizeof(char *));
  separated = separateinput(input);
  int fd = open(separated[1], O_CREAT | O_WRONLY, 0644);
  int save = dup(STDOUT_FILENO);
  dup2(fd, STDOUT_FILENO);
  execute(separated[0]);
  dup2(save, STDOUT_FILENO);
  return;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input: char *

Redirects stdin into the first parameter

Output: void
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void redirectin(char *input) {
  char** separated = malloc(2 * sizeof(char *));
  separated = separateinput(input);
  int fd = open(separated[1], O_RDONLY);
  int save = dup(STDIN_FILENO);
  dup2(fd, STDIN_FILENO);
  execute(separated[0]);
  dup2(save, STDIN_FILENO);
  return;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input: char *

Executes pipes using popen()
Executes first comment on FILE * into 2nd parameter

Output: void
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void executepipe(char *input) {
  char** separated = malloc(2 * sizeof(char *));
  separated = separateinput(input);
  FILE *file = popen(separated[0], "r");
  int fd = fileno(file);
  int save = dup(STDIN_FILENO);
  dup2(fd, STDIN_FILENO);
  close(fd);
  execute(separated[1]);
  dup2(save, STDIN_FILENO);
  return;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input: char *

Checks if the executable string has a redirect or a pipe
Returns in for what the executable arg is
0 -> None
1 -> '>'
2 -> '<'
3 -> '|'

Output: int
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int check(char* input) {
  char *found = strpbrk(input, "><|");
  if (found) {
    if (strncmp(found, ">", 1) == 0) {
      return 1;
    }
    if (strncmp(found, "<", 1) == 0) {
      return 2;
    }
    if (strncmp(found, "|", 1) == 0) {
      return 3;
    }
  }
  else {
    return 0;
  }
}
