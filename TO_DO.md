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

2) 
<< 
==54455==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x602000002913 at pc 0x00010fc5e197 bp 0x7ffedffa8cb0 sp 0x7ffedffa8ca8
READ of size 1 at 0x602000002913 thread T0
    #0 0x10fc5e196 in count_tokens input_count_tokens.c:58
    #1 0x10fc59959 in split_input_into_args input.c:47
    #2 0x10fc5874c in run_shell_loop shell.c:42
    #3 0x10fc57681 in main main.c:34
    #4 0x7fff6ffc4cc8 in start+0x0 (libdyld.dylib:x86_64+0x1acc8)
--------

# BUG:
