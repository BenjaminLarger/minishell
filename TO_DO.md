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

4)  
env var in heredoc should be replaced
bash-3.2$ cat << eof
> $USER
> eof
demre

5)  
echo -n ne marche pas si -n n'est pas en params[1].
ex: 
echo hello -n
> hello -n


--------

# CRASH:
1)  
ctr-c in here file after a few repetition crashes

2) 
ctr-d after executing "cat" without argument should display a new prompt



--------

# BUG:

1) cat on 2 consecutive prompts fail