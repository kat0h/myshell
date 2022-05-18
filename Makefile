CC = clang
CFLAGS = -Wall -I/usr/local/include

main: main.c
	$(CC) $(CFLAGS) -o main main.c
