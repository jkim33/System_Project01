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



