#ifndef SYN_H
#define SYN_H

#include <fstream>
#include <string>
#include <iostream>
#include "Token.h"
#include "Reporter.h"
#include "LexicalAnalyzer.h"

class SyntacticalAnalyzer 
{
  public:
    SyntacticalAnalyzer(std::string filename);

  private:
    tokenType token;
};
	
#endif
