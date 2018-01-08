#include "SyntacticalAnalyzer.h"

// Will open the input file and read all tokens until the end of the file
SyntacticalAnalyzer::SyntacticalAnalyzer ( std::string filename ) {
	LexicalAnalyzer lex;

  Reporter rpt; 
  rpt.open( filename );

  std::ifstream f;
  f.open( filename.c_str() );

	Token* t;
	while ((t = lex.get_token(f))->type != EOF_T) {
    rpt.reportToken( t, lex.line(), lex.position() );
    delete t;
  }
  rpt.totalErrors();
}
