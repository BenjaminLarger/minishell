# TODO:
1) Update variable global dans le shell avec errno avant de fermer child shell //to test, should be good

2) doubt => check this : Set the $PATH to a multiple directory value (directory1:directory2) and ensure that directories are checked in order from left to right.

3) 
'$' shouldn't be displayed when in front of quotes
bash-3.2$ echo $"USER"
USER
bash-3.2$ echo $ "USER"
$ USER
bash-3.2$ echo $US"ER"
ER


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
   
2)  
On devrait pouvoir lancer minishell dans minishell et verifier le sous-niveau avec echo $SHLVL