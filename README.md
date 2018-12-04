# Systems Project01
## System Level Programming - Project 01
### Composed by Jason Kim and Jackie Li

## Our Shell

Our shell mimics what a standard bash shell can do, taking in user input and allowing the user to interact with the contents of their terminal and directories. To test, simply type: 
```
make test
```
### Current Features

1. **Terminal Commands**

   Our shell can take in and parse through user input, and separate the command from its arguments. The shell reads the command, and will instruct the parent to wait until the execution has finished. The shell then forks and executes the command. Current functions include but are not limited to:

   ..*  **_ls_** -- List the current contents of the directory. This function can take in multiple arguments, such as '-a, , -l, -al'.

   ..* **_cd_** -- Changes the current directory into a new directory by moving along the contents of the paths in the terminal being ran in. This function cannot be forked and ran through a child process, so it requires our own implementation.

2. **Redirection and Pipes**

   ..* **_Semicolon commands_** -- The shell is able to run multiple commands using the semicolon ( ';' ) to separate commands. Our shell can run multiple commands in the order that they are written in.
   
   ..* **_Redirection_** -- The shell is able to redirect in and redirect out as a standard bash shell. Redirect out takes in the first command, and utilizes it for the second command. Redirect in redirects stdin from the 2nd parameter.

   ..* **_Piping_** -- Uses popen() which is then duplicated and executed onto a second parameter. Piping redirects the first command and uses it as the input of the second command.

### BUGS and ISSUES
Features yet to be implemented:

  **_Stacking Redirection_** -- We have not fully implemented the redirection options, as the shell cannot mimic the standard shell with double redirection. e.g. `wc < foo > woo` will not fully execute on its own. In general, trying to stack multiple redirects or pipes will not work.

  **_Double Redirection_** -- Our shell only replaces the inputs that we provide for redirection, but is unable to append to the output. It is not capable of handling calls such as `<<` or `>>`.
  
  **_Inconsistent Printing_** -- Pipe seems to cause some issues when it is done executing. Typically, "Write a Command: " would be shown on a new line but at times, there are 2 instead or come before the pipe is finished. We suspect that fork() is the main cause of this but we have not yet fixed it. 

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
