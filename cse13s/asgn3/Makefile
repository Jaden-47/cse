CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic 

all: tower

tower: tower.o stack.o
	$(CC) -o tower tower.o stack.o

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

tower.o: tower.c
	$(CC) $(CFLAGS) -c tower.c

clean:
	rm -rf tower *.o infer-out

infer:
	make clean; infer-capture -- make; infer-analyze -- make
