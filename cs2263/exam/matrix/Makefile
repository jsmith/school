GCC = gcc -Wall -g -Wshadow
DIFF = diff -qb
VAL = valgrind --tool=memcheck --leak-check=full

matrix: main_matrix.o matrix.o
	$(GCC) matrix.o main_matrix.o -o $@

main_matrix.o: main_matrix.c matrix.h
	$(GCC) matrix.h -c main_matrix.c

matrix.o: matrix.c matrix.h
	$(GCC) matrix.h -c matrix.c

test: testt0 test1

testt0: matrix
	$(VAL) ./matrix add input/input0 input/input1 output/output0
	$(DIFF) expected/expected0 output/output0

test1: matrix
	$(VAL) ./matrix sub input/input0 input/input1 output/output1
	$(DIFF) expected/expected1 output/output1

clean:
	rm -f matrix *.o output/* *.gch
