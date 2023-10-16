## Shell - Command-Line Interpreter Recreation
#### Description
This project is a recreation of a command-line interpreter (shell) that mirrors the functionality of sh within a limited scope.

### Synopsis
This shell includes a collection of custom-built commands and the ability to execute scripts in various paths on the host operating system.

### Environment
Our shell has been thoroughly tested on Ubuntu 14.05.5 LTS. Testing was conducted in VirtualBox on Ubuntu via Vagrant (Version 2.0.1).

### Repository Contents
File	Description
shell.h	Header file containing function prototypes
main.c	Main program file
_builtin.c	Functions for executing built-in commands
_env.c	Environmental variable handling functions
_error.c	Functions for printing error messages
_exit.c	Exit function
_realloc.c	Helper function for memory reallocation
_strtok.c	Custom strtok function
helper_func.c	String manipulation helper functions
helper_func2.c	Additional string helper functions
path.c	Functions for managing the PATH
tokenizer.c	Function for tokenizing strings
How to Use
Clone the repository:
bash
Copy code
git clone https://github.com/LiambeeKiko/simple_shell.git
Change your working directory to simple_shell:
bash
Copy code
cd simple_shell/
Compile all the .c files within the simple_shell directory:
bash
Copy code
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
Interactive and Non-Interactive Mode
In interactive mode, input is accepted from the user interactively:
bash
Copy code
$ ./hsh
$ ls -l
# Output of 'ls -l' command
$ echo hello world
### hello world
In non-interactive mode, the shell processes commands from input piped in:
bash
Copy code
$ ls -l | ./hsh
# Output of 'ls -l' command
### Built-in Commands
The shell includes the following built-in commands:

env: Prints environmental variables.
exit: Exits the shell.
pwd: Prints the current working directory.
setenv: Sets a new environmental variable.
unsetenv: Unsets an environmental variable.
For more details, refer to the man page by running:

bash
Copy code
man ./man_1_simple_shell

### Functions and System Calls Used
The project utilizes various functions and system calls including close, execve, exit, fork, free, getline, malloc, perror, and wait.

## Notes
This shell does not handle aliases, comments, or history.

## Author;
Liambee D. Age - https://twitter.com/AgeLiambee || https://github.com/LiambeeKiko || agedavid7@gmail.com

