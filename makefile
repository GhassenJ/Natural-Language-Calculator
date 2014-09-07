CC = gcc -Wall -Wextra

#CCFLAGS =
CCFLAGS = -g
#CCFLAGS = -O3 -D NDEBUG

all: calc

clean:
	rm -f calc*.o tokenize*.o token*.o stack*.o

calc: calc.o tokenize.o stack.o token.o
	$(CC) $(CCFLAGS)  calc.o tokenize.o stack.o token.o -o calc

calc.o: calc.c tokenize.h stack.h token.h
	$(CC) $(CCFLAGS) -c calc.c

tokenize.o: tokenize.c token.h tokenize.h
	$(CC) $(CCFLAGS) -c tokenize.c

token.o: token.c token.h
	$(CC) $(CCFLAGS) -c token.c

stack.o: stack.c stack.h
	$(CC) $(CCFLAGS) -c stack.c