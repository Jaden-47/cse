CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: encode decode

encode: encode.o trie.o io.o
	$(CC) -g -o encode encode.o trie.o io.o

decode: decode.o word.o io.o
	$(CC) -g -o decode decode.o io.o word.o

trie.o: trie.c trie.h
	$(CC) $(CFLAGS) -g -c trie.c

word.o: word.c word.h
	$(CC) $(CFLAGS) -g -c word.c

io.o: io.c io.h
	$(CC) $(CFLAGS) -g -c io.c

clean:
	rm -rf encode decode *.o infer-out

infer:
	make clean; infer-capture -- make; infer-analyze -- make
