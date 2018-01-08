P1.out : Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o Token.o Reporter.o
	g++ -g -o P1.out Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o Token.o Reporter.o

Project1.o : Project1.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -g -c Project1.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h Reporter.cpp Reporter.h
	g++ -g -c SyntacticalAnalyzer.cpp

token.o: Token.h Token.cpp
	g++ -g -c Token.cpp

reporter.o: Reporter.h Reporter.cpp
	g++ -g -c Reporter.cpp

clean : 
	rm *.o P1.out *.gch *.lst *.dbg
