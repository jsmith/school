default:
	echo Run \"make q1\" or \"make q2\"

q1:
	gcc -std=c99 common.h common.c q1.c

q2:
	gcc -std=c99 common.h common.c q2.c

q1_test_complex:
	make q1 && ./a.out 1 5 -5 < q1_input_complex.txt

q1_test_simple:
	make q1 && ./a.out 1 5 -5 < q1_input_simple.txt

q1_test_empty:
	make q1 && ./a.out 1 5 -5 < q1_input_empty.txt
