#ifndef REPORTER_H
#define REPORTER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Token.h"

class Reporter {
  public:
    Reporter();
    Reporter( std::string filename );
    ~Reporter();


    // Opens the required output stream such that:
    //    'filename.in' => { 'filename.lst', 'filename.dbg' }
    void open( std::string filename );

    // Handles a token input
    void reportToken( Token* t, int line, int pos );

    // Reports the total number of errors to the debug file
    void totalErrors();

  private:
    // Streams
    std::ifstream source;
    std::ofstream debug;
    std::ofstream listing;
    int errors, curLine ;

    // Reports a normal listing
    void reportListing( Token* t, int line, int pos );

    // Reports an error listing
    void reportError( Token* t, int line, int pos );

    // Reports the total number of errors to the debug file
    void reportLine();
};



#endif
