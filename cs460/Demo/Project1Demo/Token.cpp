#include "Token.h"
static const std::string Token_tokenNames[] = {
  "ERROR_T", "IDENT_T", "NUMLIT_T", "PLUS_T", "MINUS_T", "DIV_T", "MULT_T", "MOD_T", "MINUSMINUS_T", 
  "PLUSPLUS_T", "ASSIGN_T", "EQUALTO_T", "NOTEQ_T", "GT_T", "LT_T", "GTE_T", "LTE_T", 
  "LOGAND_T", "LOGOR_T", "NOT_T", "AND_T", "OR_T", "XOR_T", "SHIFTL_T", "SHIFTR_T", 
  "TILDA_T", "LPAREN_T", "RPAREN_T", "LBRACE_T", "RBRACE_T", "SEMI_T", "COMMA_T", "QUEST_T", "COLON_T",
  "EOF_T", "INTTYPE_T", "DBLTYPE_T", "MAIN_T", "IF_T", "ELSE_T", 
  "WHILE_T", "VOID_T"
};

const std::string* Token::tokenNames = Token_tokenNames;

std::string Token::typeToString( tokenType T ) {
  return Token::tokenNames[T];
}

Token::Token() {
  type = EOF_T;
  val = "";
}
