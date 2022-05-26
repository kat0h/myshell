test: ./objects/test_args
	./objects/test_args

./objects/test_args: ./objects/parser.o ./objects/test_args.o
	$(CC) -o $@ $^

./objects/parser.o: parser.c parser.h
	$(CC) -c $< -o $@

./objects/test_args.o: ./test/test_args.c
	$(CC) -c $< -o $@
