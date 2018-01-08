P1.out : Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o Reporter.o
	g++ -std=c++11 -g -o P1.out Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o Reporter.o

Project1.o : Project1.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -std=c++11 -g -c Project1.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -std=c++11 -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -std=c++11 -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h 
	g++ -std=c++11 -g -c SyntacticalAnalyzer.cpp
	
Reporter.o : Reporter.cpp
	g++ -std=c++11 -g -c Reporter.cpp
	
clean : 
	rm *.o P1.out *.lst *.dbg
run1:
	./P1.out P1-1.py
run2:
	./P1.out P1-2.py
run3:
	./P1.out P1-3.py
submit: Project1.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp SetLimits.cpp SetLimits.h Reporter.cpp makefile README.txt P1-1.py
	rm -rf gautamP1
	mkdir gautamP1
	cp Project1.cpp gautamP1
	cp LexicalAnalyzer.h gautamP1
	cp LexicalAnalyzer.cpp gautamP1
	cp SyntacticalAnalyzer.h gautamP1
	cp SyntacticalAnalyzer.cpp gautamP1
	cp SetLimits.cpp gautamP1
	cp SetLimits.h gautamP1
	cp Reporter.cpp gautamP1
	cp makefile gautamP1
	cp README.txt gautamP1
	cp P1-1.py gautamP1
	tar cfvz gautamP1.tgz gautamP1
	cp gautamP1.tgz ~tiawatts/cs460drop

	
	