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
ls "-l" devrait marcher
ls: "-l": No such file or directory
ou 
ls -l | grep "1 d"
ou
echo hello "bye"
= hello bye

