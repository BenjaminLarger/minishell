# TODO:
1) Implementer la fonction exec_cmd_if_builtin() dans le fichier shell_exec_builtin.c pour verifier et executer la commande si elle est builtin. Elle est appelée au moment d’executer les commandes dans exec_command(), fichier shell_exec_args.c

2) Gérer les permissions des fichiers lors des redirections

--------

# CRASH:
1) Quand linker en contact avec argument (pas d'espace entre l'arg et le linker)
ex: ls| cat -e
array[0]: ls|
array[1]: cat
array[2]: -e
array[3]: (null)

--------

# BUG:
1) 
ls "-l" devrait marcher
ls: "-l": No such file or directory
ou 
ls -l | grep "1 d"
ou
echo hello "bye"
= hello bye

2)
exit should work if preceded by spaces... '  	  exit'. Write builtin