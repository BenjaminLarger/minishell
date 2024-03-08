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
Si le shell exécutait directement le programme ls sans créer de fils au préalable, le processus du shell serait entièrement remplacé par le programme ls et on ne pourrait plus rien faire dans notre shell…

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
id_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
Langage du code : C++ (cpp)
La différence entre les deux se ressent surtout lorsqu’un processus a plusieurs processus fils. L’appel wait va récupérer le premier fils qui a terminé, tandis que waitpid pourra attendre le fils avec le PID qu’on lui fournit en particulier et ignorer tous les autres. De plus, waitpid nous fournit la possibilité d’indiquer certaines options.
Le paramètre commun aux deux appels système est status : un pointeur vers une variable de type int, dans lequel wait et waitpid peuvent stoker le statut de fin du processus fils qu’on récupère. On pourra ensuite analyser ce nombre pour déterminer si le fils a correctement terminé son exécution ou s’il a été interrompu par exemple.
options : il existe quelques options possibles pour waitpid. Parmi elles, l’option parfois bien utile WNOHANG, qui force waitpid à retourner immédiatement si le fils n’a pas fini son exécution. Sans cette option, le processus père restera par défaut bloqué tant que le fils n’a pas terminé.
On peut inspecter le statut à l’aide de plusieurs macros :
WIFEXITED(status) : renvoie vrai si le fils s’est terminé normalement, par exemple en faisant appel à exit ou en terminant via la fonction principale, main.
WEXITSTATUS(status) : a utiliser uniquement si WIFEXITED a renvoyé vrai. Renvoie le code de sortie du fils, c’est à dire le nombre que le fils a spécifié lors de son appel à exit ou lors de son retour dans le main.
WIFSIGNALED(status) : renvoie vrai si le fils a été terminé de force par un signal.
WTERMSIG(status) : a utiliser uniquement si WIFSIGNALED a renvoyé vrai. Renvoie le numéro du signal qui a provoqué la terminaison du fils.

signal(), sigaction(), sigemptyset(), sigaddset(), kill(): These functions are used for signal handling, including setting signal handlers, sending signals, and modifying signal sets.
C’est quelque peu sinistre, mais on peut, au besoin, tuer notre processus fils. Pour cela, il suffit d’utiliser la fonction kill de la bibliothèque <signal.h> afin d’envoyer un signal au processus fils de tout arrêter immédiatement. Le prototype de la fonction est le suivant :
sig : le signal à envoyer au processus pour le tuer. Il y a plusieurs signaux possibles qu’on peut envoyer avec kill, chacun avec ses nuances (voir man 7 signal), mais les plus courants sont sans doute SIGTERM (signal de fin) ou SIGKILL (arrêt forcé immédiat).
« L’envoi » d’un signal est en réalité plutôt une livraison : le système met à jour le contexte du processus destinataire du signal. En effet, pour chaque processus, le système maintient deux vecteurs de bits : pending pour surveiller les signaux en attente, et blocked pour suivre les signaux bloqués. Lorsqu’il envoie un signal, le système ne fait que mettre le bit associé au signal à 1 dans le vecteur pending du processus destinataire.
Il est important de noter qu’il ne peut pas y avoir plusieurs signaux du même type en attente. Dans l’image ci-dessus, le processus a déjà le signal 17, SIGCHLD, en attente. Le système ne peut donc pas lui envoyer d’autres signaux SIGCHLD jusqu’à ce que ce signal soit réceptionné. Il n’y a pas non plus de file d’attente pour les signaux en attente : tant que ce signal n’est pas réceptionné, tous les signaux du même type qui suivent sont perdus.
Cet appel système fonctionne de la même manière que la commande /bin/kill décrite ci-dessus. Ses paramètres sont :
pid : l’identifiant du processus ou du groupe de processus auquel envoyer le signal. On peut ici spécifier :
un entier positif : le PID d’un processus,
un entier négatif : le PGID d’un groupe de processus,
0 : tous les processus dans le groupe du processus appelant,
-1 : tous les processus dans le système pour lequel le processus appelant a la permission d’envoyer un signal (sauf le processus 1, init). Voir la page de manuel kill (2) pour la question des permissions.

exit(): This function is used to terminate the calling process. It would be used to exit the minishell.

getcwd(), chdir(), stat(), lstat(), fstat(), unlink(): These functions are used for directory and file manipulation, including getting the current working directory, changing directories, and obtaining file status.

execve(): This function is used to execute a program. It would be used to launch other executables within the minishell.

dup(), dup2(), pipe(): These functions are used for file descriptor manipulation and inter-process communication, including duplicating file descriptors and creating pipes for communication between processes.
Les descripteurs de fichiers d’un pipe s’utilisent de la même manière que tout autre descripteur de fichier. Afin d’y mettre des données ou de les récupérer, on pourra se servir respectivement des appels systèmes read et write de la bibliothèque <unistd.h>.
LIRE ET ECRIRE DANS UN PIPE
Il y a toutefois deux points à garder à l’esprit :
Si un processus tente de lire depuis un pipe vide, read bloquera le processus jusqu’à ce que des données soient écrites dans le pipe.
À l’inverse, si un processus tente d’écrire dans un pipe plein (c’est à dire à la limite de sa capacité), write bloquera le processus jusqu’à ce qu’assez de données soient lues pour permettre d’y écrire.

opendir(), readdir(), closedir(): These functions are used for directory operations, including opening directories, reading directory contents, and closing directories.

strerror(), perror(): These functions are used for error handling, including converting error numbers to error messages and printing error messages.

isatty(), ttyname(), ttyslot(), ioctl(): These functions are used for terminal I/O control operations, including checking if a file descriptor refers to a terminal and obtaining terminal device information.

getenv(): This function is used to retrieve the value of an environment variable. It would be used to handle environment variables in the shell.

tcsetattr(), tcgetattr(), tgetent(), tgetflag(), tgetnum(), tgetstr(), tgoto(), tputs(): These functions are used for terminal control and manipulation, including setting and getting terminal attributes and interacting with the terminal database.

## Documentation
Block signal routine : https://www.codequoi.com/envoyer-et-intercepter-un-signal-en-c/#:~:text=Sigaction%20en%20action&text=Quand%20on%20fait%20ctrl%2Dc,avec%20ctrl%2D%5C%20(%20SIGQUIT%20).