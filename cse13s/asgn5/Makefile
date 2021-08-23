CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99 

all: sorting

sorting: sorting.o bubble.o shell.o quick.o binary.o
	$(CC) -o sorting sorting.o bubble.o shell.o quick.o binary.o

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

binary.o: binary.c
	$(CC) $(CFLAGS) -c binary.c

clean:
	rm -rf sorting *.o infer-out

valgrind:
	make clean; make; valgrind ./sorting

infer:
	make clean; infer-capture -- make; infer-analyze -- make
