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