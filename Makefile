main: objects/parser.o objects/main.o objects/lex.yy.c
	$(CC) -o $@ $^

test: objects/test_parser objects/test_str
	./test/test_parser.sh
	./test/test_str.sh

objects/main.o: main.c
	$(CC) -c $< -o $@

# str
objects/str.o: str.c
	$(CC) -c $< -o $@

# parser
objects/lex.yy.c: parse.l
	flex -t parse.l > objects/lex.yy.c

objects/parser.o: parser.c
	$(CC) -c $< -o $@

# test
objects/test_parser: objects/parser.o objects/test_parser.o objects/lex.yy.c
	$(CC) -o $@ $^

objects/test_str: objects/test_str.o objects/str.o
	$(CC) -o $@ $^

objects/test_parser.o: test/test_parser.c
	$(CC) -c $< -o $@

objects/test_str.o: test/test_str.c
	$(CC) -c $< -o $@
