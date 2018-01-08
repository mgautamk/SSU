// LexicalAnalyzer.h: Will take an input stream and return a single token that is valid in our language
//                    The valid tokens are defined in Token.h and the table that we use is defined in
//                    table.h
// Arthur Wuterich
// 2/17/15

#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include "Token.h"

class LexicalAnalyzer {

  public:
    LexicalAnalyzer ();
    Token* get_token ( std::ifstream& f );
    std::string get_lexeme () const;
    int line();
    int position();
    int errors();
  private:
    int nextState( const char& c );
    tokenType identToType( const std::string& ident );
    int pos;
    int errCount;
    int lineCount;
};
	
#endif
