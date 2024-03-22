# TODO:
1) Update variable global dans le shell avec errno avant de fermer child shell //to test, should be good

2) doubt => check this : Set the $PATH to a multiple directory value (directory1:directory2) and ensure that directories are checked in order from left to right.


--------

# CRASH:
1) 
fix replacing env var within single quotes
bash-3.2$ echo "$USER"'$USER'
demre$USER
bash-3.2$ echo "$USER'$USER'"
demre'demre'

2) 
ctr-c in here file after a few repetition crashes

3) 
ctr-d after executing "cat" without argument should display a new prompt



--------

# BUG:

1) single quote should return prompt instead of exiting

2)  
< and <<  is expecting a file. Set relevant error
bash-3.2$ <<
bash: syntax error near unexpected token `newline'

3) cat on 2 consecutive prompts fail