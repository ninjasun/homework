COMPILE = gcc -Wall -g -ansi -pedantic
ASMCOMPILE = ${COMPILE} -c
all: fibonacci

fibonacci: fib.o fibonacci.c
	$(COMPILE) -o fibonacci fib.o fibonacci.c
fib.o:
	$(ASMCOMPILE) fib.s
clean:
	rm -f fib.o fibonnaci
