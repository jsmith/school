GCC = gcc -g -Wall -Wshadow
OBJS = mymatrix.o matrix.o

matrix: $(OBJS) mymatrix.h
	$(GCC) $(OBJS) -o $@

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f matrix $(OBJS) log*

testall: test0

test0: matrix
	./matrix multiplication input output
