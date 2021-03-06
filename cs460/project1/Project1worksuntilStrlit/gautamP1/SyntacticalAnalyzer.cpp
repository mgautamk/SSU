//File: SyntacticalAnalyzer.cpp
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

#include <iostream>                                                                                                                                         
#include <iomanip>                                                                                                                                          
#include <fstream>                                                                                                                                          
#include "SyntacticalAnalyzer.h"                                                                                                                            
                                                                                                                                                            
using namespace std;                                                                                                                                        
                                                                                                                                                            
SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)                                                                                                  
{                                                                                                                                                           
        lex = new LexicalAnalyzer (filename);                                                                                                               
        token_type t;                                                                                                                                       
        while ((t = lex->GetToken()) != EOF_T)                                                                                                              
        {                                                                                                                                                   
            // get a token
            //token = lex->GetToken();
            // write its name to the debug file
            // write the corresponding lexeme to the debug file                                                                                         
        }                                                                                                                                                   
}                                                                                                                                                           
                                                                                                                                                            
SyntacticalAnalyzer::~SyntacticalAnalyzer ()                                                                                                                
{                                                                                                                                                           
        delete lex;                                                                                                                                         
}                                                                                                                                                           
   