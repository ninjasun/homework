all:
	gcc -Wall -c sorted-list.c
	ar rcs libsl.a sorted-list.o
	gcc -o sl -L. -lsl main.c
clean:
	rm -f sl sorted-list.o libsl.a
