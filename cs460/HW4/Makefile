all: H4.out

H4.out: gautamH4.o vector.o fraction.o quicksort.o SetLimits.o
	gcc gautamH4.o vector.o fraction.o quicksort.o SetLimits.o -o H4.out

gautamH4.o: gautamH4.c
	gcc -c gautamH4.c

vector.o: vector.c vector.h
	gcc -c vector.c

fraction.o: fraction.c fraction.h
	gcc -c fraction.c

quicksort.o: quicksort.c quicksort.h
	gcc -c quicksort.c

SetLimits.o: SetLimits.c SetLimits.h
	gcc -c SetLimits.c

run1:
	time ./H4.out test1

run2:
	time ./H4.out test2

run3:
	time ./H4.out test3

clean:
	rm -f *.o H4*.out 

ready:
	rm -rf gautamH4
	mkdir gautamH4
	cp gautamH4.c gautamH4
	cp vector.c gautamH4
	cp vector.h gautamH4
	cp fraction.c gautamH4
	cp fraction.h gautamH4
	cp quicksort.c gautamH4
	cp quicksort.h gautamH4
	cp SetLimits.c gautamH4
	cp SetLimits.h gautamH4
	cp Makefile gautamH4
	tar cfvz gautamH4.tgz gautamH4

submit:
	cp gautamH4.tgz ~tiawatts/cs460drop

