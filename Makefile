main: myshell.tab.c lex.yy.c str.c parse.c parser.c main.c
	$(CC) -o $@ $^

# parser
lex.yy.c: myshell.l
	flex -t myshell.l > lex.yy.c

myshell.tab.c: myshell.y
	bison -d myshell.y

clean:
	trash lex.yy.c
	trash myshell.tab.*
