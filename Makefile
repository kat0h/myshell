main: ./objects/parser.o ./objects/main.o
	$(CC) -o $@ $^

test: ./objects/test_parser
	./test/test_parser.sh

./objects/test_parser: ./objects/parser.o ./objects/test_parser.o
	$(CC) -o $@ $^

./objects/parser.o: parser.c parser.h
	$(CC) -c $< -o $@

./objects/test_parser.o: ./test/test_parser.c
	$(CC) -c $< -o $@

./objects/main.o: main.c
	$(CC) -c $< -o $@
