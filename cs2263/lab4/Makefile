#
# Jacob Smith 47118500
# Raven-Lee Mills 47308881
#

GCC = gcc -g -Wall -Wshadow
VAL = valgrind --tool=memcheck --leak-check=full

two: 2.o
	$(GCC) -o two 2.o

2.o: 2.c
	$(GCC) -c 2.c

testtwo: two
	$(VAL) ./two

three: 3.o
	$(GCC) -o three 3.o

3.o: 3.c
	$(GCC) -c 3.c

testthree: three
	$(VAL) ./three

four: 4.o
	$(GCC) -o four 4.o

4.o: 4.c
	$(GCC) -c 4.c

testfour: four
	$(VAL) ./four

testall: testtwo testthree testfour