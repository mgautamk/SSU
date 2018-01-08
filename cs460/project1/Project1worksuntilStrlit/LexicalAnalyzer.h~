//File: LexicalAnalyzer.h
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

#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>

using namespace std;

enum token_type {IDENT_T, STRLIT_T, AND_T, AS_T, ASSERT_T, BREAK_T, CLASS_T, CONT_T,
DEF_T, DEL_T, ELIF_T, ELSE_T, EXCEPT_T, EXEC_T, FINALLY_T, FOR_T, FROM_T, GLOBAL_T, IF_T, IMPORT_T, 
IN_T, IS_T, LAMDA_T, NOT_T, OR_T, PASS_T, RAISE_T, RETURN_T, TRY_T, WHILE_T, WITH_T, YIELD_T, TRUE_T, FALSE_T,
NONE_T, NL_T, CR_T, TAB_T, PLUS_T, MINUS_T, MULT_T, EXP_T, DIV_T, IDIV_T, MOD_T, LT_T, GT_T, LTE_T, INTLIT_T,
CHARLIT_T, GTE_T, EQUAL_T, NOTEQ_T, LPAREN_T, RPAREN_T, LBRACKET_T, RBRACKET_T, LBRACE_T, RBRACE_T, AT_T, COMMA_T,
COLON_T, PERIOD_T, ASSIGN_T, SEMI_T, PLUSEQ_T, MINUSEQ_T, MULTEQ_T, DIVEQ_T, IDIVEQ_T, MODEQ_T, EXPEQ_T, ABS_T, 
ALL_T, ANY_T, ASCII_T, BIN_T, BOOL_T, BYTEARR_T, BYTE_T, CHR_T, DICT_T, DIR_T, DIVMD_T, ENUMR_T, FILTR_T, FLOAT_T,
FRMT_T, FZSET_T, FLTLIT_T, ERROR_T, GATTR_T, GLBLS_T, HATTR_T, HASH_T, HEX_T, INPUT_T, INT_T, ITER_T, LEN_T,
LIST_T, MAP_T, MAX_T, MIN_T, NEXT_T, OBJ_T, OCT_T, OPEN_T, POW_T, PRINT_T, RANGE_T, RVS_T, ROUND_T, SET_T,
SLICE_T, SRTD_T, STR_T, SUM_T, SUP_T, TUPL_T, EOF_T
}; 

class LexicalAnalyzer 
{
    public:
	LexicalAnalyzer (char * filename);
        ~LexicalAnalyzer ();
	token_type GetToken ();
	token_type ReturnTokens ();
	string GetTokenName (token_type t) const;
	string GetLexeme () const;
	void ReportError (const string & msg);
    private:
	ifstream input;
	ofstream listing;
        ofstream debug;
	string line;
	int linenum;
	int pos;
	string lexeme;
	int errors;
};
	
#endif