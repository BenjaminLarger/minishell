# TODO:
1) Update variable global dans le shell avec errno avant de fermer child shell //to test, should be good

2) doubt => check this : Set the $PATH to a multiple directory value (directory1:directory2) and ensure that directories are checked in order from left to right.

3) single quote should return prompt
--------

# CRASH:
1) 
fix replacing env var within single quotes
bash-3.2$ echo "$USER"'$USER'
demre$USER
bash-3.2$ echo "$USER'$USER'"
demre'demre'

2) 
<< 
bash-3.2$ <<
bash: syntax error near unexpected token `newline'

3) 
ctr-c in here file after a few repetition crashes

4) 
ctr-c after executing "cat" without argument twice does not wait for input.

5) 
ctr-d after executing "cat" without argument should display a new prompt

6) 
single quote exit exit the program => echo xwc

7) 
cd -
cd ~
cd <wrong-command>

8) 
herefile  => << infile grep READ | cat >> outfile 
==6593==ERROR: AddressSanitizer: SEGV on unknown address (pc 0x00010066e512 bp 0x7ffeef5b7eb0 sp 0x7ffeef5b7eb0 T0)
==6593==The signal is caused by a READ memory access.
==6593==Hint: this fault was caused by a dereference of a high value address (see register values below).  Dissassemble the provided pc to learn which register was used.
    #0 0x10066e512 in ft_strcmp+0x12 (minishell:x86_64+0x100027512)

9)  
Wrong n_args when using <<
ie: cat << a | cat << b
--------

# BUG:
