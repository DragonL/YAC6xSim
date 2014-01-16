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
     IDENTIFIER = 258,
     CODE_BLOCK = 259,
     LITERAL = 260,
     K_PTR = 261,
     K_ANY = 262,
     K_ALL = 263,
     K_IMM = 264,
     K_IMMZERO = 265,
     K_IMMS8 = 266,
     K_IMMU8 = 267,
     K_IMMS16 = 268,
     K_IMMU16 = 269,
     K_IMMS32 = 270,
     K_IMMU32 = 271,
     K_LOCAL = 272,
     K_FRAME = 273,
     K_NOTE = 274,
     K_TERNARY = 275,
     K_BRANCH = 276,
     K_COPY = 277,
     K_COMMUTATIVE = 278,
     K_IF = 279,
     K_CLOBBER = 280,
     K_SCRATCH = 281,
     K_SPACE = 282,
     K_STACK = 283,
     K_X87_ARITH = 284,
     K_X87_ARITH_REVERSIBLE = 285,
     K_INST_TYPE = 286,
     K_REG_CLASS = 287,
     K_LREG_CLASS = 288,
     K_MANUAL = 289,
     K_MORE_SPACE = 290
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define CODE_BLOCK 259
#define LITERAL 260
#define K_PTR 261
#define K_ANY 262
#define K_ALL 263
#define K_IMM 264
#define K_IMMZERO 265
#define K_IMMS8 266
#define K_IMMU8 267
#define K_IMMS16 268
#define K_IMMU16 269
#define K_IMMS32 270
#define K_IMMU32 271
#define K_LOCAL 272
#define K_FRAME 273
#define K_NOTE 274
#define K_TERNARY 275
#define K_BRANCH 276
#define K_COPY 277
#define K_COMMUTATIVE 278
#define K_IF 279
#define K_CLOBBER 280
#define K_SCRATCH 281
#define K_SPACE 282
#define K_STACK 283
#define K_X87_ARITH 284
#define K_X87_ARITH_REVERSIBLE 285
#define K_INST_TYPE 286
#define K_REG_CLASS 287
#define K_LREG_CLASS 288
#define K_MANUAL 289
#define K_MORE_SPACE 290




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 1648 "gen-rules-parser.y"
{
	int			tag;
	char			*name;
	struct gensel_value	*value;
	struct gensel_option	*option;
	struct
	{
		char	*filename;
		long	linenum;
		char	*block;

	}	code;
	struct
	{
		struct gensel_value	*head;
		struct gensel_value	*tail;

	}	values;
	struct
	{
		struct gensel_option	*head;
		struct gensel_option	*tail;

	}	options;
	struct
	{
		struct gensel_clause	*head;
		struct gensel_clause	*tail;

	}	clauses;
}
/* Line 1489 of yacc.c.  */
#line 151 "gen-rules-parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

