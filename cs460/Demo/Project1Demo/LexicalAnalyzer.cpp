#include "LexicalAnalyzer.h"

// Include table
#include "table.h"

LexicalAnalyzer::LexicalAnalyzer() {
  pos = errCount = 0;
  lineCount = 1;
}

int LexicalAnalyzer::line() {
  return lineCount;
}

int LexicalAnalyzer::position() {
  return pos;
}

int LexicalAnalyzer::errors() {
  return errCount;
}

// Returns the integer representation for each character of input
int LexicalAnalyzer::nextState( const char& c ) {

  int result = 0;

  // Alpha
  if( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ) {
    result = 0;

  } else 

  // Num
  if( (c >= '0' && c <= '9') ) {
    result = 2;
  } else {

    // Specials
    switch( c ) {
      case '_': result = 1; break;
      case '.': result = 3; break;
      case '+': result = 4; break;
      case '-': result = 5; break;
      case '/': result = 6; break;
      case '*': result = 7; break;
      case '%': result = 8; break;
      case '=': result = 9; break;
      case '<': result = 10; break;
      case '>': result = 11; break;
      case '&': result = 12; break;
      case '^': result = 13; break;
      case '|': result = 14; break;
      case '!': result = 15; break;
      case '~': result = 16; break;
      case '(': result = 17; break;
      case ')': result = 18; break;
      case '{': result = 19; break;
      case '}': result = 20; break;
      case ',': result = 21; break;
      case ';': result = 22; break;
      case '?': result = 23; break;
      case ':': result = 24; break;

      // The 'other' case for unexpected input
      default: result = 25; break;
    } 
  }

  return result;
}

// Converts IDENT_T types to their respective type
tokenType LexicalAnalyzer::identToType( const std::string& ident ) {
  tokenType result = IDENT_T;

  if( ident == "int") {
    result = INTTYPE_T;
  } else if ( ident == "float" ) {
    result = DBLTYPE_T ;
  } else if ( ident == "main" ) {
    result = MAIN_T;
  } else if ( ident == "if" ) {
    result = IF_T;
  } else if ( ident == "else" ) {
    result = ELSE_T;
  } else if ( ident == "while" ) {
    result = WHILE_T;
  } else if ( ident == "void" ) {
    result = VOID_T;
  }

  return result;
}

Token* LexicalAnalyzer::get_token( std::ifstream& f ) {
  int state = 0;
  char c;
  Token* T = new Token();

  // Clear spaces, newlines, and tabs in front of the line
  while( f.peek() == ' ' || f.peek() == '\n' || f.peek() == '\t') {
    c = f.get();
    if( c == '\n' ) {
      lineCount++;
      pos = 0;
    } else {
      pos++;
    }
  }

  // Read from the input stream if we have file contents
  if( !f.eof() ) {

    // Resolve the token fully
    while( state < 99 ) {
      c = f.get();
      state = sTable[state][nextState(c)];
      T->val += c;
      pos++;
    }

    // Generate the type of the token based on the state
    T->type = static_cast<tokenType>(state-99);

    // Putback if the state was not an error state;
    if( state != 99 ) {
      f.putback(c);
      T->val = T->val.substr( 0, T->val.length()-1 );
      pos--;
    } else {
      errCount++;
    }

    // Special IDENT_T handling
    if( T->type == IDENT_T ) {
      T->type = identToType( T->val );
    }
  }

  return T;
}

std::string LexicalAnalyzer::get_lexeme() const {
}

