#include <iomanip>
#include <cstdlib>
#include <string.h>
#include "LexicalAnalyzer.h"

using namespace std;

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

static int table [][27] = 
//	  a   _   0   .   ;   +   -   /   *   %   =   <   >   &   ^   |   !   ~   (   )   ;   ?   :   ,  "   \t other    
       {{ 1,  1,  2,  3, 13,  5,  6, 13, 13, 13, 13,  7,  9, 11, 13, 12, 13, 23, 23, 23, 23, 23, 23, 23, 14, 15, 32},  // 0 starting
	{ 1,  1,  1, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21},  // 1 alpha or _ (or  number)
	{22, 22,  2,  4, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22},  // 2 number
	{31, 31,  4, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31},  // 3 period
	{22, 22,  4, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29},  // 4 number for decimal all was 22 after 4
	{24, 24, 24, 24, 24, 23, 24, 24, 24, 24, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 29, 24},  // 5 plus
	{24, 24, 24, 24, 24, 24, 23, 24, 24, 24, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24},  // 6 minus
	{24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 23,  8, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24},  // 7 less than
	{24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24},  // 8 second less than
	{24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 23, 24, 10, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24},  // 9 greater than
	{24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24},  // 10 second greater than
	{24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 23, 24, 24, 23, 24, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24},  // 11 ampersand
	{24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 23, 24, 24, 24, 24, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24},  // 12 vertical bar
	{24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24},  // any other
	{24, 24, 24, 24, 24, 24, 24, 25, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25}}; // open quote


LexicalAnalyzer::LexicalAnalyzer(char * filename) {
   //Assign the last three chars of the file as file extension ".in" in our case 
    string fname = filename;
    string fileExtension = fname.substr(fname.length() -3, 3);
   
    input.open (filename);
    if (input.fail())
    {
        cout << "Input file not found\n";
        exit (1);
    }
    
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

LexicalAnalyzer::~LexicalAnalyzer ()
{
	input.close ();
	cout << errors << " errors found in input file\n";
	listing << errors << " errors found in input file" << endl;;
	listing.close();
	debug << errors << " errors found in input file\n";
	debug.close();
}

token_type LexicalAnalyzer::get_token ()
{
	token_type t = find_token ();;
	debug << "    " << left << setw (10) << get_token_name(t) << "    " << get_lexeme() << endl << right;
	return t;
}

token_type LexicalAnalyzer::find_token ()
{
         
//        for (int k= 0; k <= line.length(); k++) {
//            if (line[k] == '\t') {
//                cout << "tab found by forcing at line: " << line << "and position " << k << endl;
//                pos++;
//                lexeme = "tab";
//                return TAB_T;
//
//            }
//        }

        // Print out comment lines and empty lines as is
        while ((line[pos]) == '#' || (line[pos]) == ' ') //isspace(line[pos]))
		if ((line[pos]) == '#' || ++pos >= line.length())
		{
			getline (input, line);
			if (input.fail())
			{
				lexeme = "eof";
				return EOF_T;
			}
                      
			linenum++;
			listing << "    " << linenum << ": " << line << endl;	
			debug << "    " << linenum << ": " << line << endl;	
			line += ' ';
			pos = 0;
		}
       
        //list of valid strings in same order as in our DFA table
        static string valid = "a_0.;+-/*%=<>&^|!~();?:,\"\t";
	lexeme = "";
	int state = 0;
	while (state >= 0)
	{
		char c = line[pos++];
		lexeme += c;
                
		if (isalpha(c)) 
			c = 'a';
		else if (isdigit(c))
			c = '0';
		int col = 0;
		while (col < valid.length() && valid[col] != c)
			col++;
		state = table[state][col];
		switch (state)
		{
                    case 14: //for string literals with double quote
                        //If we have a open double quote, find everything until close double quote and put everything
                        //in between as string literal
                        if (lexeme == "\"") {
                        string templexeme = "\"";
                        int idx = 0;
		  
                        for (int j = 0; j < line.length(); j++) {
                            if (line[j] == '\"') {
                                idx = j;
                                continue;
                                }
                        }
                        for (int i = pos; i < line.length(); i++) {
                            templexeme += line[i];
                            if (line[i] == '\"') {
                                lexeme = templexeme + line[i];
                                pos = i;
                                i = line.length();
                                }
                            }
                        pos++;
                        lexeme = lexeme.erase(lexeme.length()-1,1);
                        return STRLIT_T;
                        }
                        //if not any of above or string literal, then count as error
                        error_message (string("Invalid character found: ") + lexeme);
                        return ERROR_T;
                    case 15:
                        if (lexeme == "\t") {
                            cout << "Found Tab in case 15" << endl;
                        }
                        return TAB_T;
		    case 21: // identifier, int, or double 
			pos--;
			lexeme = lexeme.erase(lexeme.length()-1,1);
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
                    case 22: //numeric literal
                        pos--;
                        lexeme = lexeme.erase(lexeme.length()-1,1);
                        return INTLIT_T;
                    case 29:  //float litral
                        pos--;
                        lexeme = lexeme.erase(lexeme.length()-1,1);
                        return FLTLIT_T;
                    case 24: //symbol with backup
                        if (lexeme == "//") return IDIV_T;
                        if (lexeme == "**") return EXP_T;
                        //if (lexeme == "//=") return IDIVEQ_T;
                        //if (lexeme == "**=") return EXPEQ_T;
                         pos--;
                         lexeme = lexeme.erase(lexeme.length()-1,1);
                    case 25:
                        if (lexeme == "//=") {
                            cout << "Found IDIVEQ" << endl;
                        }
                        if (lexeme == "**=") {
                            cout << "Found EXPEQ" << endl;
                        }
                    case 23: //symbol
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
                        error_message (string("Invalid character found: ") + lexeme);  
                        return ERROR_T;
                    case 31:
                        pos--;
                        lexeme = lexeme.erase(lexeme.length()-1,1);
                    case 32: //other characters other than period will count as errors 
                        if (lexeme == ".") return PERIOD_T;
                        if (lexeme =="{") return LBRACE_T;
                        if (lexeme == "}") return RBRACE_T;
                        if (lexeme == "@") return AT_T;
                        if (lexeme == "]") return RBRACKET_T;
                        if (lexeme == "[") return LBRACKET_T;
                        if (lexeme == "\t") {
                            cout <<"Found tab in 32" << endl;
                        }
                        //if we have a single quote, find for a finishing single quote and return 
                        //everything in between as a single string literal
                        if (lexeme == "'") {
                            string temponelexeme = "\'";
                        //cout << "This is the position" << pos << " and line is " << line << endl;
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
                                //lexeme = templexeme + line[i+1];
                                lexeme = temponelexeme + line[i];
                                pos = i;
                                //i = line.length() + 1;
                                i = line.length();
                                }
                            }
                        pos++;
                        lexeme = lexeme.erase(lexeme.length()-1,1);
                        
                        return STRLIT_T;
                            
                        }
                        //count as error if anything else in this state
                        error_message (string("Invalid character found: ") + lexeme);
			return ERROR_T;
		}
	}
}

string LexicalAnalyzer::get_token_name (token_type t) const
{
	return token_names [t];
}

string LexicalAnalyzer::get_lexeme () const
{
	return lexeme;
}

void LexicalAnalyzer::error_message (const string & msg)
{
        listing << "Error:  " << msg << " at " << linenum << ',' << pos << endl;
        debug << "Error: " << msg << " at " << linenum << ',' << pos << endl;
	errors++;
}
                        
                        
                        
                        
                        
                        
                        
                        
                        




