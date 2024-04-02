# TODO:
1) Update variable global dans le shell avec errno avant de fermer child shell //to test, should be good

2) doubt => check this : Set the $PATH to a multiple directory value (directory1:directory2) and ensure that directories are checked in order from left to right.
ex: export PATH=/usr/bin:/bin:/usr/local/bin

3)  
- On devrait pouvoir lancer minishell dans minishell (on peut verifier le sous-niveau avec echo $SHLVL)

4)  DONE
Pour les variables d'environnement:
	- passer envp dans le main
	- sauver envp dans un **char
	- ensuite on ne fait que modifier l'array que l'on passe aussi a execve.

5)  
check unset, export, cd souldn't work when followed by pipe
ex: export VAR=1 | wc

6)  
interactive mode si pipe en fin de ligne pour pouvoir faire:
bash-3.2$ ls |
> cat -e

7)  
Si pas de pipe dans l'input, executer sans pipe

8)  
return FAILURE des qu'un infile n'existe pas dans handle_redirections_until_next_pipe

--------

# CRASH:
1)  
ctr-c in here file after a few repetition crashes

2) 
ctr-d after executing "cat" without argument should display a new prompt

3)  
SEGV dans builtin_cd.c:128 quand on fait cd .. apres avoir supprimer le repertoire actuel. 

bash-3.2$ pwd
/Users/demre/Documents/test1
bash-3.2$ ls
bash-3.2$ mkdir test2
bash-3.2$ ls
test2
bash-3.2$ cd test2/
bash-3.2$ pwd
/Users/demre/Documents/test1/test2
bash-3.2$ rmdir ../test2/
bash-3.2$ pwd							// n'affiche rien dans notre minishell
/Users/demre/Documents/test1/test2
bash-3.2$ cd ..							// SEGV
bash-3.2$ pwd
/Users/demre/Documents/test1
bash-3.2$ ls
bash-3.2$


--------

# BUG:

1) cat on 2 consecutive prompts fail

2)  Fix builtin_export
Export rajoute une ligne alors que la variable d'environmment existe deja.
minish> export VAR=hello
minish> export VAR=-bye
minish> env | grep VAR
VAR=hello
VAR=-bye

3b)  
Permettre d'utiliser += avec export?

minish> export VAR=hello
minish> export VAR+=-bye
minish> env | grep VAR
VAR=hello
VAR+=-bye

bash-3.2$ export VAR=hello
bash-3.2$ export VAR+=-bye
bash-3.2$ env | grep VAR
VAR=hello-bye

2)  Fix builtin_unset using env_msh