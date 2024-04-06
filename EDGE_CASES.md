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

ls >> outfile -l			// add 'ls -l' to outfile
ls >> outfile1 -l > outfile2	// print 'ls -l' to outfile2, and leave outfile unchanged or create empty outfile
cat < infile -e			// read infile and add cat -e
cat < infile1 -e < infile2	// read infile2 and add cat -e. Stop if no infile1.
cat < infile1 > outfile -e < infile2	// read infile2, add cat -e, write to outfile
cat < infile < infile2 > outfile -e > outfile2	// read infile2, add cat -e, create empty outfile, write to outfile2

If (chmod u-w outfile) and (no infile2)
	cat < infile > outfile -e < infile2
	bash: outfile: Permission denied

	cat < infile < infile2 > outfile -e
	bash: infile2: No such file or directory

If (no outfile) and (no infile2)
	cat < infile > outfile -e < infile2
	bash: infile2: No such file or directory		(but outfile created)

	cat < infile < infile2 > outfile -e
	bash: infile2: No such file or directory		(no outfile created)

	cat < < infile > outfile -e < infile2  (double linker)
	bash: syntax error near unexpected token `<'	(no outfile created)

In bash:
cat -e << eof1 < infile << eof2
> aa
> eof1
> bb
> eof2
bb$
cat -e << eof1 < infile << eof2 < infile
> aa
> eof1
> bb
> eof2
whateverwaininfile$

In bash:
bash-3.2$ echo $USER
demre
bash-3.2$ echo "$USER"
demre
bash-3.2$ echo '$USER'
$USER
bash-3.2$ echo " '$USER' "
'demre'
bash-3.2$ echo ' "$USER" '
"$USER"
bash-3.2$ echo "   $USER$USER    Q"
   demredemre    Q
bash-3.2$ echo "   $USER     $USER    Q"
   demre     demre    Q
bash-3.2$ echo $USER"$USER"'$USER' " '$USER' $"$' "$USER" '
demredemre$USER 'demre' $ "$USER"

bash-3.2$ echo $"er"
er
bash-3.2$ echo $ "er"
$ er

-----

bash-3.2$ ls <
bash: syntax error near unexpected token `newline'
bash-3.2$ <
bash: syntax error near unexpected token `newline'
bash-3.2$ >
bash: syntax error near unexpected token `newline'
bash-3.2$ <<
bash: syntax error near unexpected token `newline'
bash-3.2$ >>
bash: syntax error near unexpected token `newline'
bash-3.2$ < <<
bash: syntax error near unexpected token `<<'
bash-3.2$ ls < |
bash: syntax error near unexpected token `|'
bash-3.2$ ls > |
bash: syntax error near unexpected token `|'
bash-3.2$ ls | <
bash: syntax error near unexpected token `newline'

bash-3.2$ <>>
bash: syntax error near unexpected token `>'
bash-3.2$ <<>>
bash: syntax error near unexpected token `>>'
bash-3.2$ <<>
bash: syntax error near unexpected token `>'
bash-3.2$ <<<
bash: syntax error near unexpected token `newline'

-----------------

bash-3.2$ export test
bash-3.2$ env | grep test
bash-3.2$

bash-3.2$ export test=
bash-3.2$ env | grep test
test=
export test=te.st
bash-3.2$ env | grep test
test=te.st

bash-3.2$ export =test
bash: export: `=test': not a valid identifier
bash-3.2$ export te.st=
bash: export: `te.st=': not a valid identifier

bash-3.2$ export VAR=aaaatest VA.R2=bbbbtest VAR3 VAR4+=cccctest
bash: export: `VA.R2=bbbbtest': not a valid identifier
bash-3.2$ env | grep VAR
VAR=aaaatest
VAR4=cccctest

------------

bash-3.2$ ls -l > infile > infile2
(creates empty infile and filled infile2)

bash-3.2$ ls -l > infile | wc | cat -e
       0       0       0$		(+ creates infile correctly)

bash-3.2$ ls -l > infile | wc > infile2
(creates filled infile and filled infile2)

bash-3.2$ ls -l > infile | ls -m > infile2
(creates filled infile and filled infile2)
