GCC = gcc -Wall -g -Wshadow

1: 1.o
	$(GCC) 1.o -o $@

1.o: 1.c
	$(GCC) 1.c -c

test: 1
	./1

clean:
	rm -f *.o 1 a.out
