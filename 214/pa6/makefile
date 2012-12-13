books:
	gcc -lpthread books.c -o books
clean: 
	rm -f books
test:
	./books database.txt orders.txt \"SPORTS01 HOUSING01 POLITICS01\"

.PHONY: test clean
