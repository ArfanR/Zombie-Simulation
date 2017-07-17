/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TINTEGER = 258,
     TLBRACE = 259,
     TRBRACE = 260,
     TSEMI = 261,
     TLPAREN = 262,
     TRPAREN = 263,
     TIF = 264,
     TELSE = 265,
     TMAIN = 266,
     TROTATE = 267,
     TFORWARD = 268,
     TATTACK = 269,
     TRANGED_ATTACK = 270,
     TIS_HUMAN = 271,
     TIS_ZOMBIE = 272,
     TIS_PASSABLE = 273,
     TIS_RANDOM = 274
   };
#endif
/* Tokens.  */
#define TINTEGER 258
#define TLBRACE 259
#define TRBRACE 260
#define TSEMI 261
#define TLPAREN 262
#define TRPAREN 263
#define TIF 264
#define TELSE 265
#define TMAIN 266
#define TROTATE 267
#define TFORWARD 268
#define TATTACK 269
#define TRANGED_ATTACK 270
#define TIS_HUMAN 271
#define TIS_ZOMBIE 272
#define TIS_PASSABLE 273
#define TIS_RANDOM 274




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 17 "zompiler.y"
{
    Node* node;
	NBlock* block;
	NStatement* statement;
	NNumeric* numeric;
	NBoolean* boolean;
	std::string* string;
	int token;
}
/* Line 1529 of yacc.c.  */
#line 97 "parser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE zompilerlval;

