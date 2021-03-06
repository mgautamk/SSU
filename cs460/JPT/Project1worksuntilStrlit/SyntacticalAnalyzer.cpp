#include <iostream>                                                                                                                                         
#include <iomanip>                                                                                                                                          
#include <fstream>                                                                                                                                          
#include "SyntacticalAnalyzer.h"                                                                                                                            
                                                                                                                                                            
using namespace std;                                                                                                                                        
                                                                                                                                                            
SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)                                                                                                  
{                                                                                                                                                           
        lex = new LexicalAnalyzer (filename);                                                                                                               
        token_type t;                                                                                                                                       
        while ((t = lex->get_token()) != EOF_T)                                                                                                              
        {                                                                                                                                                   
            // get a token
            //token = lex->get_token();
            // write its name to the debug file
            // write the corresponding lexeme to the debug file                                                                                         
        }                                                                                                                                                   
}                                                                                                                                                           
                                                                                                                                                            
SyntacticalAnalyzer::~SyntacticalAnalyzer ()                                                                                                                
{                                                                                                                                                           
        delete lex;                                                                                                                                         
}                                                                                                                                                           
   