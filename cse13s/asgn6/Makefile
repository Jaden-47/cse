CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99 

all: hatterspeak

hatterspeak: hatterspeak.o speck.o hash.o ll.o parser.o bf.o bv.o
	$(CC) -o hatterspeak hatterspeak.o speck.o hash.o ll.o parser.o bf.o bv.o

hatterspeak.o: hatterspeak.c
	$(CC) $(CFLAGS) -c hatterspeak.c

speck.o: speck.c speck.h
	$(CC) $(CFLAGS) -c speck.c

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) -c hash.c

ll.o: ll.c ll.h
	$(CC) $(CFLAGS) -c ll.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

bf.o: bf.c bf.h bv.h bv.c parser.c parser.h
	$(CC) $(CFLAGS) -c bf.c

bv.o: bv.c bv.h
	$(CC) $(CFLAGS) -c bv.c
clean:
	rm -rf hatterspeak *.o infer-out

valgrind:
	make clean; make; valgrind ./hatterspeak

infer:
	make clean; infer-capture -- make; infer-analyze -- make
