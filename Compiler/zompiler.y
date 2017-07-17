%{
#include "node.h"
#include "parser.hpp"
#include <iostream>
#include <string>
extern int yylex();
extern void yyerror(const char* s);

// Global for the main block
NBlock* g_MainBlock = nullptr;

// Disable the warnings that Bison creates
#pragma warning(disable: 4065)
%}

/* Add one union member for each Node* type */
%union {
    Node* node;
	NBlock* block;
	NStatement* statement;
	NNumeric* numeric;
	NBoolean* boolean;
	std::string* string;
	int token;
}

%error-verbose

/* Terminal symbols */
%token <string> TINTEGER
%token <token> TLBRACE TRBRACE TSEMI TLPAREN TRPAREN
%token <token> TIF TELSE
%token <token> TMAIN TROTATE TFORWARD TATTACK TRANGED_ATTACK
%token <token> TIS_HUMAN TIS_ZOMBIE TIS_PASSABLE TIS_RANDOM

/* Statements */
%type <block> main_loop block
%type <statement> statement if rotate forward attack ranged_attack

/* Expressions */
%type <numeric> numeric
%type <boolean> boolean is_human is_zombie is_passable is_random

%%

main_loop	: TMAIN TLBRACE block TRBRACE
{
    g_MainBlock = $3;
    g_MainBlock->SetMainBlock();
    std::cout << "Main entry point found!" << std::endl;
};

block		: statement
{
    $$ = new NBlock();
    $$->AddStatement($1);
    std::cout << "Single statement" << std::endl;
}
                    | block statement
{
    $$->AddStatement($2);
    std::cout << "Multiple statements" << std::endl;
};

statement	:       if
                    | rotate TSEMI
                    | forward TSEMI
                    | attack TSEMI
                    | ranged_attack TSEMI
;

if			: TIF TLPAREN boolean TRPAREN TLBRACE block TRBRACE

{
    $$ = new NIf($3, $6);
    std:: cout << "If statement" << std::endl;
};
                    | TIF TLPAREN boolean TRPAREN TLBRACE block TRBRACE TELSE TLBRACE block TRBRACE
{
    $$ = new NIf($3, $6, $10);
    std::cout << "If else statement" << std::endl;
};

rotate		: TROTATE TLPAREN numeric TRPAREN
{
    $$ = new NRotate($3);
    std::cout << "Rotate command" << std::endl;
};

forward		: TFORWARD TLPAREN TRPAREN
{
    $$ = new NForward();
    std::cout << "Forward command" << std::endl;
};

attack		: TATTACK TLPAREN TRPAREN
{
    $$ = new NAttack();
    std::cout << "Attack command" << std::endl;
};

ranged_attack: TRANGED_ATTACK TLPAREN TRPAREN
{
    $$ = new NRangedAttack();
    std::cout << "Ranged_attack command" << std::endl;
};

numeric		: TINTEGER
{
    $$ = new NNumeric(*($1));
    std::cout << "Numeric value of " << *($1) <<
    std::endl;
};

boolean		: is_human
                    | is_zombie
                    | is_passable
                    | is_random
;

is_human	: TIS_HUMAN TLPAREN numeric TRPAREN
{
    $$ = new NIsHuman($3);
    std::cout << "Is_human command" << std::endl;
};

is_zombie	: TIS_ZOMBIE TLPAREN numeric TRPAREN
{
    $$ = new NIsZombie($3);
    std::cout << "Is_zombie command" << std::endl;
};

is_passable	: TIS_PASSABLE TLPAREN TRPAREN
{
    $$ = new NIsPassable();
    std::cout << "Is_passable command" << std::endl;
};

is_random	: TIS_RANDOM TLPAREN TRPAREN
{
    $$ = new NIsRandom();
    std::cout << "Is_random command" << std::endl;
};

%%
