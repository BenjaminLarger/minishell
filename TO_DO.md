# TODO:
1) Update variable global dans le shell avec errno avant de fermer child shell
--------

# CRASH:
1) Quand linker en contact avec argument (pas d'espace entre l'arg et le linker)
ex: ls| cat -e
array[0]: ls|
array[1]: cat
array[2]: -e
array[3]: (null)

2) 
Quand deux groupements avec guillemets sont en contact
echo "hel""lo"

3) 
echo $variable_qui_n'existe_pas
--------

# BUG:
1) 
exit should work if preceded by spaces... '  	  exit'. Write builtin
bash-3.2$ "    exit"
bash:     exit: command not found
		!=
bash-3.2$     exit
exit
=> ft_split
