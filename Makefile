main: objects/parser.o objects/main.o objects/lex.yy.c
	$(CC) -o $@ $^

test: objects/test_parser
	./test/test_parser.sh

objects/test_parser: objects/parser.o objects/test_parser.o objects/lex.yy.c
	$(CC) -o $@ $^

objects/parser.o: parser.c parser.h
	$(CC) -c $< -o $@

objects/test_parser.o: test/test_parser.c
	$(CC) -c $< -o $@

objects/main.o: main.c
	$(CC) -c $< -o $@

objects/lex.yy.c: parse.l
	flex -t parse.l > objects/lex.yy.c
