#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

//separates the string based on the semicolons
//returns an array of executable strings
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

//used to separate executable strings with >, <, or |
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

//used to change directories (cd)
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

//executes all executable strings that don't involve a redirect or a pipe
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

void redirectout(char *input) {
  char** separated = malloc(2 * sizeof(char *));
  int fd = open(separated[1], O_CREAT | O_WRONLY, 0644);
}

void redirectin(char *input) {
  
}

void pipe(char *input) {

}

//checks if the executable string has a redirect or a pipe
//0 = None
//1 = >
//2 = <
//3 = |
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

//runs the shell
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
	execute(separated([i]));
      }
      else if (c == 1) {
	redirectout(separated[i]);
      }
      else if (c == 2) {
	redirectin(separated[i]);
      }
      else if (c == 3) {
	pipe(separated[i]);
      }
      i++;
    }
  }
}
