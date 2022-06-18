#
# Makefile 2022@kotakato
#

main: myshell.tab.c lex.yy.c str.c parse.c parser.c main.c exec.c
	$(CC) -o $@ $^
	ctags -R
	make clean

parser: myshell.tab.c lex.yy.c str.c parse.c parser.c exec.c
	$(CC) -O0 -g -o $@ -DPARSER_MAIN $^

# parser
lex.yy.c: myshell.l
	flex -t myshell.l > lex.yy.c

myshell.tab.c: myshell.y
	bison -d myshell.y

clean:
	trash lex.yy.c
	trash myshell.tab.*
