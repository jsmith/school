#
# Jacob Smith 47118500
# Raven-Lee Mills 47308881
#

GCC = gcc -g -Wall -Wshadow
HDRS = vector.h sort.h search.h
OBJS = search.o sort.o
DIFF = diff

main: $(OBJS) $(HDRS) main.c
	$(GCC) $(OBJS) $(HDRS) main.c -o main -lm

sort.o: sort.c sort.h
	$(GCC) -c sort.c sort.h

search.o: search.c search.h
	$(GCC) -c search.c search.h

test0: main
	./main < input0 > output0.txt
	$(DIFF) expected0 output0.txt

test1: main
	./main < input1 > output1.txt
	$(DIFF) expected1 output1.txt

testall: test1 test0

clean:
	rm -f output* *.o *.gch