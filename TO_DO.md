mkdir# TODO:
1)  
builtin commands unset, export, cd souldn't work when followed by pipe
ex: export VAR=1 | wc

2)  
interactive mode si pipe en fin de ligne pour pouvoir faire:
bash-3.2$ ls |
> cat -e

3)  
return FAILURE des qu'un infile n'existe pas dans handle_redirections_until_next_pipe

--------

# CRASH:

--------

# BUG:

1)  Fix builtin_unset using env_msh
