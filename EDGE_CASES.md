In shell:

- When has a space inside >> or <<:
ls -l > > outfile
zsh: parse error near `>'
grep 8 < < eof
zsh: parse error near `<'

- When has a space missing before/after quotes:
ls -l | tr ' '_
ls -l | tr e' '
usage: tr [-Ccsu] string1 string2
       tr [-Ccu] -d string1
       tr [-Ccu] -s string1
       tr [-Ccu] -ds string1 string2


grep i < infile
==
< infile | grep i

ls -l | < infile | cat -e // should work