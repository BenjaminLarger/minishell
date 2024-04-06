# TODO:



1)  
Quand une commande n'a pas d'output, comment faire passer quelque chose pour la commande suivante?

ls -l > infile | wc > infile2 fonctionne correctement

Probleme avec
	ls -l > infile | wc | cat -e
ou
	export VAR=1 | wc
Les deux devraient retourner:
       0       0       0

J'ai cree la fonction 'handle_output_redirection_before_pipe' dans shell_redirections_handle.c pour creer un fichier vide a passer.
Ca resoud 'ls -l > infile | wc | cat -e', mais ca casse 'ls -l > infile | wc > infile2' 😬🤷‍♂️
Et puis ca ne resoud pas 'export VAR=1 | wc' (j'avais pas realise que c'etait un probleme plus global) ou plus generalement si une commande n'a pas d'output a faire passer. C'est pas un probleme specifique aux redirections du coup.
Je ne pense pas qu'utiliser handle_output_redirection_before_pipe soit la chose a faire.

On pourrait avoir une fonction dans le reset de exec_args ou a la fin de la boucle

1)  
builtin commands unset, export, cd souldn't work when followed by pipe
ex: export VAR=1 | wc
previous input not passed



--------

# CRASH:

--------

# BUG:

