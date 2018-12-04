# Systems Project01
## System Level Programming - Project 01
### Composed by Jason Kim and Jackie Li

## Our Shell

Our shell mimics what a standard bash shell can do, taking in user input and allowing the user to interact with the contents of their terminal and directories.

### Current Features

1. **Terminal Commands**

   Our shell can take in and parse through user input, and separate the command from its arguments. The shell reads the command, and will instruct the parent to wait until the execution has finished. The shell then forks and executes the command. Current functions include but are not limited to:

   ..*  **_ls_** -- List the current contents of the directory. This function can take in multiple arguments, such as '-a, , -l, -al'.

   ..* **_cd_** -- Changes the current directory into a new directory by moving along the contents of the paths in the terminal being ran in. This function cannot be forked and ran through a child process, so it requires our own implementation.

### BUGS and ISSUES


### Function Headers

```C
separate(char * input)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input: char *

Utilizes strsep to detect and split a string by semicolons and removes whitespaces
Returns an array of executable strings

Output: char **
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

separateinput(char * input)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input: char *
Takes in a string of executables
Separates the string by either a ">", ">", or "|"

Outputs an array of executable terminal calls
Output: char **
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

changedir(char * input)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input: char *
Forks and changes the directory to the input value

Returns a void as we are only modifying the directory
Output: returns void
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

execute(char * input)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input: char *

Executes all executable strings that don't involve a redirect or a pipe
Forks and executes based on the string

Output: void
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

redirectout(char * input)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input: char *

Redirects the first input into 2nd file, overwrites

Output: void
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

redirectin(char * input)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input: char *
Redirects stdin into the first parameter
Output: void
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

executepipe(char * input)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Input: char *

Executes pipes using popen()
Executes first comment on FILE * into 2nd parameter

Output: void
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int check(char * input)
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
```