%option nounistd
%option nounput
%option never-interactive

%{
// Disable warnings
#pragma warning(disable: 4018)
#pragma warning(disable: 4996)
#pragma warning(disable: 4005)

#include <string>
#include <iostream>
#include "node.h"
#include "parser.hpp"
extern YYSTYPE zompilerlval;
#define SAVE_TOKEN zompilerlval.string = new std::string(yytext, yyleng)
#define TOKEN(t) (zompilerlval.token = t)
extern "C" int yywrap() { return 1; }
int g_LineNumber = 1;
%}

%%

[ \t]					{ }
[0-9]+					{ SAVE_TOKEN; return TINTEGER; }

"main_loop"				{ return TOKEN(TMAIN); }
"{"						{ return TOKEN(TLBRACE); }
"}"						{ return TOKEN(TRBRACE); }
";"						{ return TOKEN(TSEMI); }
"("						{ return TOKEN(TLPAREN); }
")"						{ return TOKEN(TRPAREN); }

"if"					{ return TOKEN(TIF); }
"else"					{ return TOKEN(TELSE); }

"rotate"				{ return TOKEN(TROTATE); }
"forward"				{ return TOKEN(TFORWARD); }
"attack"				{ return TOKEN(TATTACK); }
"ranged_attack"			{ return TOKEN(TRANGED_ATTACK); }

"is_human"				{ return TOKEN(TIS_HUMAN); }
"is_zombie"				{ return TOKEN(TIS_ZOMBIE); }
"is_passable"			{ return TOKEN(TIS_PASSABLE); }
"is_random"				{ return TOKEN(TIS_RANDOM); }

"//".*"\n"				{ g_LineNumber++; }

%{
/* Do not add any of your own tokens below this line!!!! */
%}

"\n"					{ g_LineNumber++; }

[a-zA-Z_]+				{ std::cout << "ERROR: Unknown token '" << yytext << "' on line " << g_LineNumber << std::endl; yyterminate(); }

.						{ std::cout << "ERROR: Unknown token '" << yytext << "' on line " << g_LineNumber << std::endl; yyterminate(); }

%%
