H3.out : gautamH3.o fraction.o SetLimits.o
	g++ -o H3.out gautamH3.o fraction.o SetLimits.o

T3.out : gautamT3.o fraction.o SetLimits.o
	g++ -o T3.out gautamT3.o fraction.o SetLimits.o

gautamH3.o : gautamH3.cpp SetLimits.h fraction.h
	g++ -c gautamH3.cpp -g

gautamT3.o : gautamT3.cpp SetLimits.h fraction.h
	g++ -c gautamT3.cpp -g

fraction.o : fraction.cpp fraction.h
	g++ -c fraction.cpp -g

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -c SetLimits.cpp -g

run1 : H3.out sample.in
	./H3.out sample.in

run2 : T3.out sample.in
	./T3.out sample.in
clean :
	rm -f *.o H3*.out T3*.out

submit : gautamH3.cpp gautamT3.cpp fraction.h fraction.cpp SetLimits.h SetLimits.cpp Makefile README.txt sample.in
	rm -rf gautamH3
	mkdir gautamH3
	cp gautamH3.cpp gautamH3
	cp gautamT3.cpp gautamH3
	cp fraction.h gautamH3
	cp fraction.cpp gautamH3
	cp SetLimits.h gautamH3
	cp SetLimits.cpp gautamH3
	cp Makefile gautamH3
	cp README.txt gautamH3
	cp sample.in gautamH3
	tar cfvz gautamH3.tgz gautamH3
	cp gautamH3.tgz ~tiawatts/cs460drop
