P1.out : Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o 
	g++ -std=c++11 -g -o P1.out Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o 

Project1.o : Project1.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -std=c++11 -g -c Project1.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -std=c++11 -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -std=c++11 -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h 
	g++ -std=c++11 -g -c SyntacticalAnalyzer.cpp
clean : 
	rm *.o P1.out *.lst *.dbg
