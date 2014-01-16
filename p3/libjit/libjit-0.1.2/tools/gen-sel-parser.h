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
     K_PTR = 260,
     K_REG = 261,
     K_LREG = 262,
     K_FREG = 263,
     K_IMM = 264,
     K_IMMZERO = 265,
     K_IMMS8 = 266,
     K_IMMU8 = 267,
     K_IMMS16 = 268,
     K_IMMU16 = 269,
     K_LOCAL = 270,
     K_SPILL_BEFORE = 271,
     K_BINARY = 272,
     K_UNARY = 273,
     K_UNARY_BRANCH = 274,
     K_BINARY_BRANCH = 275,
     K_UNARY_NOTE = 276,
     K_BINARY_NOTE = 277,
     K_TERNARY = 278,
     K_STACK = 279,
     K_ONLY = 280,
     K_MORE_SPACE = 281,
     K_MANUAL = 282,
     K_INST_TYPE = 283
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define CODE_BLOCK 259
#define K_PTR 260
#define K_REG 261
#define K_LREG 262
#define K_FREG 263
#define K_IMM 264
#define K_IMMZERO 265
#define K_IMMS8 266
#define K_IMMU8 267
#define K_IMMS16 268
#define K_IMMU16 269
#define K_LOCAL 270
#define K_SPILL_BEFORE 271
#define K_BINARY 272
#define K_UNARY 273
#define K_UNARY_BRANCH 274
#define K_BINARY_BRANCH 275
#define K_UNARY_NOTE 276
#define K_BINARY_NOTE 277
#define K_TERNARY 278
#define K_STACK 279
#define K_ONLY 280
#define K_MORE_SPACE 281
#define K_MANUAL 282
#define K_INST_TYPE 283




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 704 "gen-sel-parser.y"
{
	char		   *name;
	struct
	{
		char	   *filename;
		long		linenum;
		char	   *block;
	}				code;
	int				options;
	struct
	{
		int			elem[8];
		int			size;

	}				pattern;
	struct
	{
		struct gensel_clause *head;
		struct gensel_clause *tail;

	}				clauses;
}
/* Line 1489 of yacc.c.  */
#line 128 "gen-sel-parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

