# TODO:

1)  
"env | grep VAR" renvoie exit code 1 s'il n'y a pas de VAR

2) update last_exit_status to 0 correctly
En fait remettre last_exit_status a 0 dans reset n'etait pas une bonne idee parce que ca affichera toujours 0 quand on fait echo $? 😬

3)  
check piping in dup zhen executing commands

4)  
Check error handling with herefile

--------

# CRASH:

--------

# BUG:

1) 
quand on ecrit dans minsh prompt puis ctrl-\ -> le contenu s'efface + retour au debut de la ligne
