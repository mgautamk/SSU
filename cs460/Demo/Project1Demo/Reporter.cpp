#include "Reporter.h"

Reporter::Reporter() {
  curLine = 0;
  errors = 0;
}

Reporter::Reporter( std::string filename ) {
  open( filename );
}

Reporter::~Reporter() {
  listing.flush(); listing.close();
  debug.flush(); debug.close();
}

// Opens the required output stream such that:
//    'filename.in' => { 'filename.lst', 'filename.dbg' }
// also opens the source file on another handle to allow reading of the lines
// for debug output
void Reporter::open( std::string filename ) {
  source.open( filename.c_str() );
  listing.open( (filename.substr(0,filename.length()-3)+".lst").c_str() );
  debug.open( (filename.substr(0,filename.length()-3)+".dbg").c_str() );
  listing << "Lexical listing for file:\t" << filename << std::endl << std::endl;
  debug << "Debug output listing for file:\t" << filename << std::endl << std::endl;
  errors = 0;
}

void Reporter::reportLine() {
  curLine++;

  // Get the next line from the source file
  std::string line;
  std::getline( source, line );
  listing << line << std::endl; 
  debug   << line << std::endl; 
}

// Handles a token input
void Reporter::reportToken( Token* t, int line, int pos ) {
  if( line > curLine ) {
    reportLine();
  }

  if( t->type == ERROR_T ) {
    reportError( t, line, pos );
  } else {
    reportListing( t, line, pos );
  }

  //std::cout << Token::typeToString( t->type ) << " : " << t->val << std::endl;
}

// Reports a normal listing
void Reporter::reportListing( Token* t, int line, int pos ) {
  listing << "\t" << line << ":" << pos << "\t" << Token::typeToString( t->type ) << "\t" << t->val << std::endl;
}

// Reports an error listing
void Reporter::reportError( Token* t, int line, int pos ) {
  listing << "\tError\t" << line << ":" << pos << "\tInvalid characters found '" << t->val << "'" << std::endl;
  debug   << "\tError\t" << line << ":" << pos << "\tInvalid characters found '" << t->val << "'" << std::endl;
  errors++;
}

// Reports the total number of errors to the debug file
void Reporter::totalErrors() {
  debug << errors << " errors found in input file" << std::endl;
  std::cout << errors << std::endl;
}
