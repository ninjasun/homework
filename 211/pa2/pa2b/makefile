COMPILER = gcc
CCFLAGS  = -Wall -g -ansi -pedantic
all: prime

prime: prime.s
	$(COMPILER) $(CCFLAGS) -o prime prime.s

clean:
	rm -f prime
