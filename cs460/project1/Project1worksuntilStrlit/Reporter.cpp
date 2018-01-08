//File: Reporter.cpp
//Author: Mahesh Gautam
//Class: CS 460
//Instructor: Dr. Tia Watts
//Date/Semester: Spring 2016
//Assignment: Project 1 aka Lexical Analyzer
//Description: This program reads in a source file (.in or .py) and produces a listing file (.lst) and
//a debugging (.dbg) file. The listing file contains the lines of input file with line numbers and errors.
//The debugging file contains the lines of input file with line numbers, errors, and following each line,
//a list of the lexemes found on the line and their corresponding tokens. This analyzer recognizes lexemes 
//for identifiers, numeric literals and symbols that were given in a hand-out. 

#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <string> 
#include "LexicalAnalyzer.h"

//Destructor, This function will complete the execution of the lexical analyzer class
LexicalAnalyzer::~LexicalAnalyzer ()
{
	input.close ();
        cout << errors << " errors found in input file\n";  //display number of errors before closing files 
	listing << errors << " errors found in input file" << endl;;
	debug << errors << " errors found in input file\n"; 
        listing.close();
	debug.close();
}

//This function will be called to write error messages to lst and dbg files
void LexicalAnalyzer::ReportError (const string & msg)
{
        listing << "Error:  " << msg << " at " << linenum << ',' << pos << endl;
        debug << "Error: " << msg << " at " << linenum << ',' << pos << endl;
	errors++;
}
   

