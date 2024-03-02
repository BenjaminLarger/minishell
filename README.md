# Architecture

## 1. Main program entry
Execution of the shell begin.
Start the shell loop

## 2. Read input
Prompt user for input => readline function
Add command to the history (global variable ?)
Handle whitespace
History => Type a command line, then use ctrl-C and press "Enter". The buffer should be clean and there should be nothing left to execute.
Can we navigate through history using Up and Down? Can we retry some command?
Execute commands that should not work like 'dsbksdgbksdghsd'. Ensure minishell doesn't crash and prints an error.
'cat | cat | ls' should behave in a "normal way".
Try to execute a long command with a ton of arguments.

## 3. Input parsing
Parse into individual command and argument
Handle special chararcter like quotes => ft_split version

## 4. Command execution
handle wrong command
handle special character $? + $
Handle absolute command (/bin/ls) and relative command
Handle empty command ""
execve

## 5. Redirection and pipe
Handle input/output redirection
Execute commands with redirections < and/or >
Repeat multiple times with different commands and arguments and sometimes change > with >>
Check if multiple tries of the same redirections fail.
Test << redirection (it doesn't have to update the history
Execute commands with pipes like 'cat file | grep bla | more'
Repeat multiple times with different commands and arguments.
Try some wrong commands like 'ls filethatdoesntexist | grep bla | more'
Try to mix pipes and redirections.

## 6. Built-in commands
### echo
handle n option
### cd
Use the command cd to move the working directory and check if you are in the right directory with /bin/ls
Repeat multiple times with working and not working cd
Also, try '.' and '..' as arguments.
### pwd
### export
Export environment variables, create new ones and replace old ones.
Check the result with env.
### unset
Export environment variables, create new ones and replace old ones.
Use unset to remove some of them.
Check the result with env.
### env
### exit
handle with or without arguments
handle minishell relaunch



## 7. Signal function
The signal handling module manages signals like SIGINT (Ctrl+C), SIGQUIT (Ctrl+), and SIGTERM => signal function
ctrl-C => display new line
ctrl-C in a prompt after you wrote some stuff should display a new line with a new prompt.
Try ctrl-C after running a blocking command like cat without arguments or grep “something“.
ctrl-\ => do not display anything
Try ctrl-\ after running a blocking command like cat without arguments or grep “something“.
ctrl-D in an empty prompt should quit minishell --> RELAUNCH!
ctrl-D in a prompt after you wrote some stuff should not do anything.
Try ctrl-D after running a blocking command like cat without arguments or grep “something“.


## 8. Environment variable
The environment variables module handles expansion of environment variables (e.g., $PATH, $HOME, etc.) in command arguments. It replaces variable names with their corresponding values.
 '$USER' must print "$USER"
Execute commands but this time without any path (ls, wc, awk and so forth).
Unset the $PATH and ensure commands are not working anymore.
Set the $PATH to a multiple directory value (directory1:directory2) and ensure that directories are checked in order from left to right.
Execute echo with some environment variables ($variable) as arguments.
Check that $ is interpreted as an environment variable.
Check that double quotes interpolate $.
Check that USER exists. Otherwise, set it.
echo "$USER" should print the value of the USER variable.

## 9. Exit status
The exit status handling module tracks the exit status of the most recently executed command and provides it for use with $?.

## 10. Error handling
The error handling module manages error messages and reports errors encountered during command execution or shell operation.

## 13. Free list
Handle memory leaks

## 14. Utils


# Functions
readline(): This function is used to read a line from the standard input. In the context of the minishell, it's likely used to get commands entered by the user.

rl_clear_history(): This function clears the history list maintained by the readline library. It might be used to clear command history in the shell.

rl_on_new_line(): This function is a hook called by readline when a new line is inserted into the input stream. It could be used to perform certain actions when a new line is encountered.

rl_replace_line(): This function replaces the current contents of the readline line buffer with a new line. It could be used to manipulate the input line.

rl_redisplay(): This function redisplays the current input line using the contents of the readline line buffer. It could be used to refresh the display after manipulation.

add_history(): This function adds a line to the history list. It's used to store commands entered by the user for later retrieval.

printf(): This function is used to print formatted output to the standard output. In the context of the minishell, it would be used for displaying prompts, messages, or command outputs.

malloc(): This function is used to dynamically allocate memory. It would be used for memory allocation within the shell program.

free(): This function is used to deallocate memory previously allocated by malloc. It's essential for preventing memory leaks in the shell program.

write(): This function is used to write data to a file descriptor. In the context of the shell, it would be used for various output operations.

access(), open(), read(), close(): These functions are used for file operations like checking file accessibility, opening files, reading from them, and closing them.

fork(), wait(), waitpid(), wait3(), wait4(): These functions are used for process management, including creating child processes, waiting for them to terminate, and obtaining their status.

signal(), sigaction(), sigemptyset(), sigaddset(), kill(): These functions are used for signal handling, including setting signal handlers, sending signals, and modifying signal sets.

exit(): This function is used to terminate the calling process. It would be used to exit the minishell.

getcwd(), chdir(), stat(), lstat(), fstat(), unlink(): These functions are used for directory and file manipulation, including getting the current working directory, changing directories, and obtaining file status.

execve(): This function is used to execute a program. It would be used to launch other executables within the minishell.

dup(), dup2(), pipe(): These functions are used for file descriptor manipulation and inter-process communication, including duplicating file descriptors and creating pipes for communication between processes.

opendir(), readdir(), closedir(): These functions are used for directory operations, including opening directories, reading directory contents, and closing directories.

strerror(), perror(): These functions are used for error handling, including converting error numbers to error messages and printing error messages.

isatty(), ttyname(), ttyslot(), ioctl(): These functions are used for terminal I/O control operations, including checking if a file descriptor refers to a terminal and obtaining terminal device information.

getenv(): This function is used to retrieve the value of an environment variable. It would be used to handle environment variables in the shell.

tcsetattr(), tcgetattr(), tgetent(), tgetflag(), tgetnum(), tgetstr(), tgoto(), tputs(): These functions are used for terminal control and manipulation, including setting and getting terminal attributes and interacting with the terminal database.