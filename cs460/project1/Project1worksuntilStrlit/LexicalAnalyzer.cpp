//File: LexicalAnalyzer.cppx
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

using namespace std;

//name of all tokens in same order as the Enum in .h file 
static string token_names[] = { "IDENT_T", "STRLIT_T", "AND_T", "AS_T", "ASSERT_T", "BREAK_T", "CLASS_T", "CONT_T",
"DEF_T", "DEL_T", "ELIF_T", "ELSE_T", "EXCEPT_T", "EXEC_T", "FINALLY_T", "FOR_T", "FROM_T", "GLOBAL_T", "IF_T", 
"IMPORT_T", "IN_T", "IS_T", "LAMDA_T", "NOT_T", "OR_T", "PASS_T", "RAISE_T", "RETURN_T", "TRY_T", "WHILE_T", 
"WITH_T", "YIELD_T", "TRUE_T", "FALSE_T", "NONE_T", "NL_T", "CR_T", "TAB_T", "PLUS_T", "MINUS_T", "MULT_T", "EXP_T", 
"DIV_T", "IDIV_T", "MOD_T", "LT_T", "GT_T", "LTE_T", "INTLIT_T", "CHARLIT_T", "GTE_T", "EQUAL_T", "NOTEQ_T", "LPAREN_T", 
"RPAREN_T", "LBRACKET_T", "RBRACKET_T", "LBRACE_T", "RBRACE_T", "AT_T", "COMMA_T", "COLON_T", "PERIOD_T", "ASSIGN_T", 
"SEMI_T", "PLUSEQ_T", "MINUSEQ_T", "MULTEQ_T", "DIVEQ_T", "IDIVEQ_T", "MODEQ_T", "EXPEQ_T", "ABS_T", "ALL_T", "ANY_T", 
"ASCII_T", "BIN_T", "BOOL_T", "BYTEARR_T", "BYTE_T", "CHR_T", "DICT_T", "DIR_T", "DIVMD_T", "ENUMR_T", "FILTR_T", 
"FLOAT_T", "FRMT_T", "FZSET_T", "FLTLIT_T", "ERROR_T", "GATTR_T", "GLBLS_T", "HATTR_T", "HASH_T", "HEX_T", "INPUT_T", 
"INT_T", "ITER_T", "LEN_T", "LIST_T", "MAP_T", "MAX_T", "MIN_T", "NEXT_T", "OBJ_T", "OCT_T", "OPEN_T", "POW_T", 
"PRINT_T", "RANGE_T", "RVS_T", "ROUND_T", "SET_T", "SLICE_T", "SRTD_T", "STR_T", "SUM_T", "SUP_T", "TUPL_T","EOF_T"};

static int DFA [][29] = 
// In order:   a_0.;+-/*%=<>&^|!~();?:,\"\t\n\r (left to right) 
       {{ 1,  1,  2,  3, 13,  5,  6, 13, 13, 13, 13,  7,  9, 11, 13, 12, 13, 20, 20, 20, 20, 20, 20, 20, 14, 15, 16, 17, 40},  
	{ 1,  1,  1, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18},  
	{19, 19,  2,  4, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19},  
	{39, 39,  4, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39},  
	{19, 19,  4, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29},   
	{21, 21, 21, 21, 21, 20, 21, 21, 21, 21, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},  
	{21, 21, 21, 21, 21, 21, 20, 21, 21, 21, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},  
	{21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 20,  8, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},  
	{21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},  
	{21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 20, 21, 10, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},  
	{21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},  
	{21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 20, 21, 21, 20, 21, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},  
	{21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 20, 21, 21, 21, 21, 20, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},  
	{21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},  
	{21, 21, 21, 21, 21, 21, 21, 22, 22, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 16, 22, 22}}; 

//This function will initiate the lexical analyzer class
LexicalAnalyzer::LexicalAnalyzer(char * filename) {
   //Assign the last three chars of the file as file extension ".in" in our case 
    string fname = filename;
    string fileExtension = fname.substr(fname.length() -3, 3);
   
    input.open (filename);
    if (input.fail())
    {
        cout << "Input file was not found\n";
        exit (1);
    }
    //create listing and debugging files
    string listingfile = fname.substr(0, fname.length()-3) + ".lst";
    listing.open (listingfile.c_str());
    string debugfile = fname.substr (0, fname.length()-3) + ".dbg"; 
    debug.open (debugfile.c_str());
    line = " ";
    linenum = 0;
    pos = 0;
    lexeme = "";
    errors = 0;    
}

//Gets the tokens returned by ReturnTokens function
token_type LexicalAnalyzer::GetToken ()
{
	token_type token = ReturnTokens ();;
        if (line != "\n" && line.length() >= 3) //so it only prints to debug if the line isn't empty or a new line
	debug << "    " << left << setw (10) << GetTokenName(token) << "    " << GetLexeme() << endl << right;
	return token;
}

//This function returns individual tokens associated with the lexemes
// This function will find the next lexeme int the input file and return
// the token_type value associated with that lexeme
token_type LexicalAnalyzer::ReturnTokens ()
{
        // Print out comment lines and empty lines as is
        while ((line[pos]) == '#' || (line[pos]) == ' ') 
		if ((line[pos]) == '#' || ++pos >= line.length())
		{
		  //close_q = false;
			getline (input, line);
			close_q = false;
                        line += "\n";  // add newline since getline doesn't get the new line character
			if (input.fail())
			{
				lexeme = "eof";
				return EOF_T;
			} 
			linenum++;
                        string templine = line;
                        templine.pop_back();
			listing << "    " << linenum << ": " << templine << endl;	
			debug << linenum << ": " << templine << endl;	
			line += ' ';
			pos = 0;
		}

        //list of valid Char AndSymbols  in same order as in our DFA 
        static string possible = "a_0.;+-/*%=<>&^|!~();?:,\"\t\n\r";
	lexeme = "";
	string lextemp2 = "";
	int state = 0; //initialize state to zero and keep going when its more than zero
	while (state >= 0 && line != "\n")
	{
		char c = line[pos++];
		lexeme += c;
                
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
			c = 'a';
                }
		else if ((c >= '0' && c <= '9')) {
			c = '0';
                }
		int col = 0;
		while (col < possible.length() && possible[col] != c) 
			col++;
		state = DFA[state][col];
		switch (state)
		{
                    case 14: //for string literals with double quote
                        //If we have a open double quote, find everything until close double quote and put everything
                        //in between as string literal
		      // string lextemp2 = "";
		      if (lexeme == "\"") {
                        string templexeme = "\"";
                        int idx = 0;

			if (close_q == false) 
			  for (int j = pos; j < line.length(); j++) {
                            if (line[j] == '\"') {
			      idx = j;
			      close_q = true;
			      break;
			    }
			    lextemp2 += line[j];
			  }
			if (close_q == true) {
                        for (int i = pos; i < line.length(); i++) {
                            templexeme += line[i];
                            if (line[i] == '\"') {
                                lexeme = templexeme + line[i];
                                pos = i;
                                i = line.length();
			    }
			}
			}
			cout << "Before close_q == false:  " << endl; 
			if (close_q == false) {
			  cout << " After close_q == false: " << endl;
			  lexeme = lextemp2;
			  pos = line.length() * 2;
			  state = 0;
			  //ReportError (string("Invalid character found: ") + lexeme);
			  return ERROR_T;
			}
			  
                        pos++;
                        lexeme.pop_back();
                        return STRLIT_T;
		      }
		      
                        //if not any of above or string literal, then count as error
                      //  ReportError (string("Invalid character found: ") + lexeme);
		      // return ERROR_T;
		      
                    case 16: //for new lines
                        //pos++;
                        if (lexeme == "\n") {
                            string templexeme = "\\";
                            lexeme = templexeme + "n";
                        }
                        return NL_T;
                    case 15: //for Tabs
                        if (lexeme == "\t") {
                            string templexeme = "\\";
                            lexeme = templexeme + "t";
                        }
                        return TAB_T;
                    case 17: //for carriage return 
                        if (lexeme == "\r") {
                            string templexeme = "\\";
                            lexeme = templexeme + "r";
                        }
                        return CR_T;
                    
		    case 18: // identifiers
			pos--;
			lexeme.pop_back();
			if (lexeme == "int") return INT_T;
                        if (lexeme == "and") return AND_T;
                        if (lexeme == "as") return AS_T;
                        if (lexeme == "assert") return ASSERT_T;
                        if (lexeme == "break") return BREAK_T;
                        if (lexeme == "class") return CLASS_T;
                        if (lexeme == "continue") return CONT_T;
                        if (lexeme == "def") return DEF_T;
                        if (lexeme == "del") return DEL_T;
                        if (lexeme == "elif") return ELIF_T;
                        if (lexeme == "else") return ELSE_T;
                        if (lexeme == "except") return EXCEPT_T;
                        if (lexeme == "exec") return EXEC_T;
                        if (lexeme == "finally") return FINALLY_T;
                        if (lexeme == "for") return FOR_T;
                        if (lexeme == "from") return FROM_T;
                        if (lexeme == "global") return GLOBAL_T;
                        if (lexeme == "if") return IF_T;
                        if (lexeme == "import") return IMPORT_T;
                        if (lexeme == "in") return IN_T;
                        if (lexeme == "is") return IS_T;
                        if (lexeme == "lambda") return LAMDA_T;
                        if (lexeme == "not") return NOT_T;
                        if (lexeme == "or") return OR_T;
                        if (lexeme == "pass") return PASS_T;
                        if (lexeme == "raise") return RAISE_T;
                        if (lexeme == "return") return RETURN_T;
                        if (lexeme == "try") return TRY_T;
                        if (lexeme == "while") return WHILE_T;
                        if (lexeme == "with") return WITH_T;
                        if (lexeme == "yield") return YIELD_T;
                        if (lexeme == "TRUE") return TRUE_T;
                        if (lexeme == "FALSE") return FALSE_T;
                        if (lexeme == "None") return NONE_T;
                        if (lexeme == "abs") return ABS_T;
                        if (lexeme == "all") return ALL_T;
                        if (lexeme == "any") return ANY_T;
                        if (lexeme == "ascii") return ASCII_T;
                        if (lexeme == "bin") return BIN_T;
                        if (lexeme == "bool") return BOOL_T;
                        if (lexeme == "bytearray") return BYTEARR_T;
                        if (lexeme == "bytes") return BYTE_T;
                        if (lexeme == "chr") return CHR_T;
                        if (lexeme == "dict") return DICT_T;
                        if (lexeme == "dir") return DIR_T;
                        if (lexeme == "divmod") return DIVMD_T;
                        if (lexeme == "enumerate") return ENUMR_T;
                        if (lexeme == "float") return FLOAT_T;
                        if (lexeme == "format") return FRMT_T;
                        if (lexeme == "frozenset") return FZSET_T;
                        if (lexeme == "getattr") return GATTR_T;
                        if (lexeme == "globals") return GLBLS_T;
                        if (lexeme == "hasattr") return HATTR_T;
                        if (lexeme == "hash") return HASH_T;
                        if (lexeme == "hex") return HEX_T;
                        if (lexeme == "input") return INPUT_T;
                        if (lexeme == "iter") return ITER_T;
                        if (lexeme == "len") return LEN_T;
                        if (lexeme == "list") return LIST_T;
                        if (lexeme == "map") return MAP_T;
                        if (lexeme == "max") return MAX_T;
                        if (lexeme == "min") return MIN_T;
                        if (lexeme == "next") return NEXT_T;
                        if (lexeme == "object") return OBJ_T;
                        if (lexeme == "oct") return OCT_T;
                        if (lexeme == "open") return OPEN_T;
                        if (lexeme == "pow") return POW_T;
                        if (lexeme == "print") return PRINT_T;
                        if (lexeme == "range") return RANGE_T;
                        if (lexeme == "reversed") return RVS_T;
                        if (lexeme == "round") return ROUND_T;
                        if (lexeme == "set") return SET_T;
                        if (lexeme == "slice") return SLICE_T;
                        if (lexeme == "sorted") return SRTD_T;
                        if (lexeme == "str") return STR_T;
                        if (lexeme == "sum") return SUM_T;
                        if (lexeme == "super") return SUP_T;
                        if (lexeme == "tuple") return TUPL_T;
			return IDENT_T;
                    case 19: //Integer literal
                        pos--;
                        lexeme.pop_back();
                        return INTLIT_T;
                    case 29:  //Float literal
                        pos--;
                        lexeme.pop_back();
                        return FLTLIT_T;
                    case 21: //symbols with more than two chars i.e IDIVEQ_T and EXPEQ_T
                        if (lexeme == "//" || lexeme == "**") {
                            if (lexeme == "//") {
                            if(line[pos+3] == '=') {
                                pos++;
                                lexeme = "//=";
                                return IDIVEQ_T;
                                }
                                return IDIV_T;
                            }
                            else if (lexeme == "**") {
                                if(line[pos] == '=') {
                                pos++;
                                lexeme = "**=";
                                return EXPEQ_T;
                                }
                                return EXP_T;    
                            }
                        }
                         pos--;
                         lexeme.pop_back();
                    case 22: //may not need
                        //may need to remove this 
                    case 20: //symbols
                        if (lexeme == "+") return PLUS_T;
                        if (lexeme == "-") return MINUS_T;
                        if (lexeme == "*") return MULT_T;
                        if (lexeme == "/") return DIV_T;
                        if (lexeme == "%") return MOD_T;
                        if (lexeme == "<") return LT_T;
                        if (lexeme == ">") return GT_T;
                        if (lexeme == "<=") return LTE_T;
                        if (lexeme == ">=") return GTE_T;
                        if (lexeme == "==") return EQUAL_T;
                        if (lexeme == "!=") return NOTEQ_T;
                        if (lexeme == "(") return LPAREN_T;
                        if (lexeme == ")") return RPAREN_T;
                        if (lexeme == ",") return COMMA_T;
                        if (lexeme == ":") return COLON_T;
                        if (lexeme == ";") return SEMI_T;
                        if (lexeme == "=") return ASSIGN_T;
                        if (lexeme == "+=") return PLUSEQ_T;
                        if (lexeme == "-=") return MINUSEQ_T;
                        if (lexeme == "*=") return MULTEQ_T;
                        if (lexeme == "/=") return DIVEQ_T;
                        if (lexeme == "%=") return MODEQ_T;
                        //anything else should be displayed and counted as errors
                        ReportError (string("Invalid character found case 20: ") + lexeme);  
                        return ERROR_T;
                    case 39:
                        pos--;
                        lexeme.pop_back();
                    case 40: //more characters 
                        if (lexeme == ".") return PERIOD_T;
                        if (lexeme =="{") return LBRACE_T;
                        if (lexeme == "}") return RBRACE_T;
                        if (lexeme == "@") return AT_T;
                        if (lexeme == "]") return RBRACKET_T;
                        if (lexeme == "[") return LBRACKET_T;
                        //if we have a single quote, find for a finishing single quote and return 
                        //everything in between as a single string literal
                        if (lexeme == "'") {
                            string temponelexeme = "\'";
                        //cout << "This is the position" << pos << " and line is " << line << endl;  //for debug
                        int idx = 0;
		  
                        for (int j = 0; j < line.length(); j++) {
                            if (line[j] == '\'') {
                                idx = j;
                                continue;
                                }
                        }
                        for (int i = pos; i < line.length(); i++) {
                            temponelexeme += line[i];
                            if (line[i] == '\'') {
                                lexeme = temponelexeme + line[i];
                                pos = i;
                                i = line.length();
                                }
                            }
			pos--;
                        lexeme.pop_back();
                        return CHARLIT_T;
                            
                        }
                        //count as error if anything else in this state
                        ReportError (string("Invalid character found: case 40") + lexeme);
			return ERROR_T;
		}
	}
}
//This function will return the token name string for the token
string LexicalAnalyzer::GetTokenName (token_type t) const
{
	return token_names [t];
}

//This function will return the lexeme found by the most recent call to 
//the getToken function
string LexicalAnalyzer::GetLexeme () const
{
	return lexeme;
}               
                        
                        
                        
                        
                        
                        
                        
                        




