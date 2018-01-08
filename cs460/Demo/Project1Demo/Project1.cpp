#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "SetLimits.h"
#include "SyntacticalAnalyzer.h"
#include "LexicalAnalyzer.h"
#include "Reporter.h"

int main (int argc, char * argv[]) {
	if (argc < 2) {
		printf ("format: proj1 <filename>\n");
		exit (1);
	}

	SetLimits();

  SyntacticalAnalyzer parse(static_cast<std::string>(argv[1]));
  
  std::cout << "Number of Errors found: \n";
	return 0;
}
