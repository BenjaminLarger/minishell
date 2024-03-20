# TODO:
1) Update variable global dans le shell avec errno avant de fermer child shell //to test, should be good
--------

# CRASH:
1) 
fix replacing env var within single quotes
bash-3.2$ echo "$USER"'$USER'
demre$USER
bash-3.2$ echo "$USER'$USER'"
demre'demre'
--------

# BUG:
