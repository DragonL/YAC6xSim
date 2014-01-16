/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "gen-sel-parser.y"

/*
 * gen-sel-parser.y - Bison grammar for the "gen-sel" program.
 *
 * Copyright (C) 2004  Southern Storm Software, Pty Ltd.
 *
 * This file is part of the libjit library.
 *
 * The libjit library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * The libjit library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the libjit library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <stdio.h>
#ifdef HAVE_STRING_H
	#include <string.h>
#elif defined(HAVE_STRINGS_H)
	#include <strings.h>
#endif
#ifdef HAVE_STDLIB_H
	#include <stdlib.h>
#endif

/*
 * Imports from the lexical analyser.
 */
extern int yylex(void);
extern void yyrestart(FILE *file);
#ifdef YYTEXT_POINTER
extern char *yytext;
#else
extern char yytext[];
#endif

/*
 * Report error messages from the parser.
 */
static void yyerror(char *msg)
{
	puts(msg);
}

/*
 * Current file and line number.
 */
extern char *gensel_filename;
extern long gensel_linenum;

/*
 * Instruction type for the "inst" variable.
 */
static char *gensel_inst_type = "unsigned char *";
static int gensel_new_inst_type = 0;

/*
 * Amount of space to reserve for the primary instruction output.
 */
static int gensel_reserve_space = 32;
static int gensel_reserve_more_space = 128;

/*
 * First register in a stack arrangement.
 */
static int gensel_first_stack_reg = 8;	/* st0 under x86 */

/*
 * Option values.
 */
#define	GENSEL_OPT_SPILL_BEFORE			0x0001
#define	GENSEL_OPT_BINARY				0x0002
#define	GENSEL_OPT_UNARY				0x0004
#define	GENSEL_OPT_TERNARY				0x0008
#define	GENSEL_OPT_STACK				0x0010
#define	GENSEL_OPT_UNARY_BRANCH			0x0020
#define	GENSEL_OPT_BINARY_BRANCH		0x0040
#define	GENSEL_OPT_ONLY					0x0080
#define	GENSEL_OPT_MANUAL				0x0100
#define	GENSEL_OPT_UNARY_NOTE			0x0200
#define	GENSEL_OPT_BINARY_NOTE			0x0400
#define	GENSEL_OPT_MORE_SPACE			0x0800

/*
 * Pattern values.
 */
#define	GENSEL_PATT_END					0
#define	GENSEL_PATT_REG					1
#define	GENSEL_PATT_LREG				2
#define	GENSEL_PATT_FREG				3
#define	GENSEL_PATT_IMM					4
#define	GENSEL_PATT_IMMZERO				5
#define	GENSEL_PATT_IMMS8				6
#define	GENSEL_PATT_IMMU8				7
#define	GENSEL_PATT_IMMS16				8
#define	GENSEL_PATT_IMMU16				9
#define	GENSEL_PATT_LOCAL				10

/*
 * Information about clauses.
 */
typedef struct gensel_clause *gensel_clause_t;
struct gensel_clause
{
	int				pattern[8];
	char		   *filename;
	long			linenum;
	char		   *code;
	gensel_clause_t	next;
};

/*
 * Free a list of clauses.
 */
static void gensel_free_clauses(gensel_clause_t clauses)
{
	gensel_clause_t next;
	while(clauses != 0)
	{
		next = clauses->next;
		free(clauses->code);
		free(clauses);
		clauses = next;
	}
}

/*
 * Declare the register variables that are needed for a set of clauses.
 */
static void gensel_declare_regs(gensel_clause_t clauses, int options)
{
	int have_reg1 = 0;
	int have_reg2 = 0;
	int have_reg3 = 0;
	int have_imm = 0;
	int have_local = 0;
	int index;
	while(clauses != 0)
	{
		for(index = 0; clauses->pattern[index] != GENSEL_PATT_END; ++index)
		{
			switch(clauses->pattern[index])
			{
				case GENSEL_PATT_REG:
				case GENSEL_PATT_LREG:
				case GENSEL_PATT_FREG:
				{
					if(index == 0)
						have_reg1 = 1;
					else if(index == 1)
						have_reg2 = 1;
					else
						have_reg3 = 1;
				}
				break;

				case GENSEL_PATT_IMMZERO: break;

				case GENSEL_PATT_IMM:
				case GENSEL_PATT_IMMS8:
				case GENSEL_PATT_IMMU8:
				case GENSEL_PATT_IMMS16:
				case GENSEL_PATT_IMMU16:
				{
					have_imm = 1;
				}
				break;

				case GENSEL_PATT_LOCAL:
				{
					have_local = 1;
				}
				break;
			}
		}
		clauses = clauses->next;
	}
	if(have_reg1)
	{
		printf("\tint reg;\n");
	}
	if(have_reg2 && (options & GENSEL_OPT_STACK) == 0)
	{
		printf("\tint reg2;\n");
	}
	if(have_reg3 && (options & GENSEL_OPT_STACK) == 0)
	{
		printf("\tint reg3;\n");
	}
	if(have_imm)
	{
		printf("\tjit_nint imm_value;\n");
	}
	if(have_local)
	{
		printf("\tjit_nint local_offset;\n");
	}
}

/*
 * Output the code within a clause.
 */
static void gensel_output_clause_code(gensel_clause_t clause)
{
	char *code;
	int index;

	/* Output the line number information from the original file */
	printf("#line %ld \"%s\"\n", clause->linenum, clause->filename);

	/* Output the clause code */
	printf("\t\t");
	code = clause->code;
	while(*code != '\0')
	{
		if(*code == '$' && code[1] >= '1' && code[1] <= '9')
		{
			index = code[1] - '1';
			switch(clause->pattern[index])
			{
				case GENSEL_PATT_REG:
				case GENSEL_PATT_LREG:
				case GENSEL_PATT_FREG:
				{
					if(index == 0)
						printf("_jit_reg_info[reg].cpu_reg");
					else if(index == 1)
						printf("_jit_reg_info[reg2].cpu_reg");
					else
						printf("_jit_reg_info[reg3].cpu_reg");
				}
				break;

				case GENSEL_PATT_IMM:
				case GENSEL_PATT_IMMZERO:
				case GENSEL_PATT_IMMS8:
				case GENSEL_PATT_IMMU8:
				case GENSEL_PATT_IMMS16:
				case GENSEL_PATT_IMMU16:
				{
					printf("imm_value");
				}
				break;

				case GENSEL_PATT_LOCAL:
				{
					printf("local_offset");
				}
				break;
			}
			code += 2;
		}
		else if(*code == '%' && code[1] >= '1' && code[1] <= '9')
		{
			index = code[1] - '1';
			switch(clause->pattern[index])
			{
				case GENSEL_PATT_REG:
				case GENSEL_PATT_LREG:
				case GENSEL_PATT_FREG:
				{
					if(index == 0)
						printf("_jit_reg_info[_jit_reg_info[reg].other_reg].cpu_reg");
					else if(index == 1)
						printf("_jit_reg_info[_jit_reg_info[reg2].other_reg].cpu_reg");
					else
						printf("_jit_reg_info[_jit_reg_info[reg3].other_reg].cpu_reg");
				}
				break;
			}
			code += 2;
		}
		else if(*code == '\n')
		{
			putc(*code, stdout);
			putc('\t', stdout);
			++code;
		}
		else
		{
			putc(*code, stdout);
			++code;
		}
	}
	printf("\n");
}

/*
 * Output a single clause for a rule.
 */
static void gensel_output_clause(gensel_clause_t clause, int options)
{
	/* Cache the instruction pointer into "inst" */
	if(gensel_new_inst_type)
	{
		printf("\t\tjit_gen_load_inst_ptr(gen, inst);\n");
	}
	else
	{
		printf("\t\tinst = (%s)(gen->posn.ptr);\n", gensel_inst_type);
		printf("\t\tif(!jit_cache_check_for_n(&(gen->posn), %d))\n",
			   (((options & GENSEL_OPT_MORE_SPACE) == 0)
			   		? gensel_reserve_space : gensel_reserve_more_space));
		printf("\t\t{\n");
		printf("\t\t\tjit_cache_mark_full(&(gen->posn));\n");
		printf("\t\t\treturn;\n");
		printf("\t\t}\n");
	}

	/* Output the clause code */
	gensel_output_clause_code(clause);

	/* Copy "inst" back into the generation context */
	if(gensel_new_inst_type)
	{
		printf("\t\tjit_gen_save_inst_ptr(gen, inst);\n");
	}
	else
	{
		printf("\t\tgen->posn.ptr = (unsigned char *)inst;\n");
	}
}

/*
 * Output the clauses for a rule.
 */
static void gensel_output_clauses(gensel_clause_t clauses, int options)
{
	const char *arg1;
	const char *arg2;
	const char *arg3;
	const char *arg;
	const char *reg;
	const char *flag1;
	const char *flag2;
	const char *flag3;
	const char *flag;
	int destroy1;
	int destroy2;
	int destroy3;
	int destroy;
	gensel_clause_t clause;
	int first, index;
	int check_index;

	/* If the clause is manual, then output it as-is */
	if((options & GENSEL_OPT_MANUAL) != 0)
	{
		gensel_output_clause_code(clauses);
		return;
	}

	/* Determine the location of this instruction's arguments */
	if((options & GENSEL_OPT_TERNARY) != 0)
	{
		arg1 = "insn->dest";
		arg2 = "insn->value1";
		arg3 = "insn->value2";
		flag1 = "DEST";
		flag2 = "VALUE1";
		flag3 = "VALUE2";
		destroy1 = 0;
		destroy2 = 0;
		destroy3 = 0;
	}
	else
	{
		arg1 = "insn->value1";
		arg2 = "insn->value2";
		arg3 = "??";
		flag1 = "VALUE1";
		flag2 = "VALUE2";
		flag3 = "??";
		if((options & (GENSEL_OPT_BINARY_BRANCH |
					   GENSEL_OPT_UNARY_BRANCH |
					   GENSEL_OPT_BINARY_NOTE |
					   GENSEL_OPT_UNARY_NOTE)) != 0)
		{
			destroy1 = 0;
		}
		else
		{
			destroy1 = 1;
		}
		destroy2 = 0;
		destroy3 = 0;
	}

	/* If all of the clauses start with a register, then load the first
	   value into a register before we start checking cases */
	check_index = 0;
	if((options & (GENSEL_OPT_BINARY | GENSEL_OPT_UNARY |
				   GENSEL_OPT_BINARY_BRANCH | GENSEL_OPT_UNARY_BRANCH |
				   GENSEL_OPT_BINARY_NOTE | GENSEL_OPT_UNARY_NOTE)) != 0 &&
	   (options & GENSEL_OPT_STACK) == 0)
	{
		clause = clauses;
		while(clause != 0)
		{
			if(clause->pattern[0] != GENSEL_PATT_REG &&
			   clause->pattern[0] != GENSEL_PATT_LREG &&
			   clause->pattern[0] != GENSEL_PATT_FREG)
			{
				break;
			}
			clause = clause->next;
		}
		if(!clause)
		{
			printf("\treg = _jit_regs_load_value(gen, %s, %d, ",
				   arg1, destroy1);
			printf("(insn->flags & (JIT_INSN_%s_NEXT_USE | "
								   "JIT_INSN_%s_LIVE)));\n", flag1, flag1);
			check_index = 1;
		}
	}

	/* Output the clause checking and dispatching code */
	clause = clauses;
	first = 1;
	while(clause != 0)
	{
		if(clause->next)
		{
			if(first)
				printf("\tif(");
			else
				printf("\telse if(");
			for(index = check_index; clause->pattern[index]; ++index)
			{
				if(index == 0)
					arg = arg1;
				else if(index == 1)
					arg = arg2;
				else
					arg = arg3;
				switch(clause->pattern[index])
				{
					case GENSEL_PATT_REG:
					case GENSEL_PATT_LREG:
					case GENSEL_PATT_FREG:
					{
						printf("%s->in_register", arg);
					}
					break;

					case GENSEL_PATT_IMM:
					{
						printf("%s->is_constant", arg);
					}
					break;

					case GENSEL_PATT_IMMZERO:
					{
						printf("%s->is_nint_constant && ", arg);
						printf("%s->address == 0", arg);
					}
					break;

					case GENSEL_PATT_IMMS8:
					{
						printf("%s->is_nint_constant && ", arg);
						printf("%s->address >= -128 && ", arg);
						printf("%s->address <= 127", arg);
					}
					break;

					case GENSEL_PATT_IMMU8:
					{
						printf("%s->is_nint_constant && ", arg);
						printf("%s->address >= 0 && ", arg);
						printf("%s->address <= 255", arg);
					}
					break;

					case GENSEL_PATT_IMMS16:
					{
						printf("%s->is_nint_constant && ", arg);
						printf("%s->address >= -32768 && ", arg);
						printf("%s->address <= 32767", arg);
					}
					break;

					case GENSEL_PATT_IMMU16:
					{
						printf("%s->is_nint_constant && ", arg);
						printf("%s->address >= 0 && ", arg);
						printf("%s->address <= 65535", arg);
					}
					break;

					case GENSEL_PATT_LOCAL:
					{
						printf("%s->in_frame && !(%s->in_register)", arg, arg);
					}
					break;
				}
				if(clause->pattern[index + 1])
				{
					printf(" && ");
				}
			}
			printf(")\n\t{\n");
		}
		else if(first)
		{
			printf("\t{\n");
		}
		else
		{
			printf("\telse\n\t{\n");
		}
		if((options & GENSEL_OPT_STACK) == 0 || clause->next)
		{
			for(index = check_index; clause->pattern[index]; ++index)
			{
				if(index == 0)
				{
					arg = arg1;
					reg = "reg";
					flag = flag1;
					destroy = destroy1;
				}
				else if(index == 1)
				{
					arg = arg2;
					reg = "reg2";
					flag = flag2;
					destroy = destroy2;
				}
				else
				{
					arg = arg3;
					reg = "reg3";
					flag = flag3;
					destroy = destroy3;
				}
				switch(clause->pattern[index])
				{
					case GENSEL_PATT_REG:
					case GENSEL_PATT_LREG:
					case GENSEL_PATT_FREG:
					{
						printf("\t\t%s = _jit_regs_load_value(gen, %s, %d, ",
							   reg, arg, destroy);
						printf("(insn->flags & (JIT_INSN_%s_NEXT_USE | "
											   "JIT_INSN_%s_LIVE)));\n",
							   flag, flag);
					}
					break;
	
					case GENSEL_PATT_IMMZERO: break;

					case GENSEL_PATT_IMM:
					case GENSEL_PATT_IMMS8:
					case GENSEL_PATT_IMMU8:
					case GENSEL_PATT_IMMS16:
					case GENSEL_PATT_IMMU16:
					{
						printf("\t\timm_value = %s->address;\n", arg);
					}
					break;
	
					case GENSEL_PATT_LOCAL:
					{
						printf("\t\tlocal_offset = %s->frame_offset;\n", arg);
					}
					break;
				}
			}
		}
		else
		{
			if((options & GENSEL_OPT_ONLY) != 0)
			{
				printf("\t\tif(!_jit_regs_is_top(gen, insn->value1) ||\n");
				printf("\t\t   _jit_regs_num_used(gen, %d) != 1)\n",
					   gensel_first_stack_reg);
				printf("\t\t{\n");
				printf("\t\t\t_jit_regs_spill_all(gen);\n");
				printf("\t\t}\n");
			}
			if((options & GENSEL_OPT_TERNARY) != 0)
			{
				printf("\t\treg = _jit_regs_load_to_top_three\n");
				printf("\t\t\t(gen, insn->dest, insn->value1, insn->value2,\n");
				printf("\t\t\t\t(insn->flags & (JIT_INSN_DEST_NEXT_USE | "
											   "JIT_INSN_DEST_LIVE)),\n");
				printf("\t\t\t\t(insn->flags & (JIT_INSN_VALUE1_NEXT_USE | "
											   "JIT_INSN_VALUE1_LIVE)),\n");
				printf("\t\t\t\t(insn->flags & (JIT_INSN_VALUE2_NEXT_USE | "
											   "JIT_INSN_VALUE2_LIVE)), "
											   "%d);\n",
					   gensel_first_stack_reg);
			}
			else if((options & (GENSEL_OPT_BINARY |
								GENSEL_OPT_BINARY_BRANCH)) != 0)
			{
				printf("\t\treg = _jit_regs_load_to_top_two\n");
				printf("\t\t\t(gen, insn->value1, insn->value2,\n");
				printf("\t\t\t\t(insn->flags & (JIT_INSN_VALUE1_NEXT_USE | "
											   "JIT_INSN_VALUE1_LIVE)),\n");
				printf("\t\t\t\t(insn->flags & (JIT_INSN_VALUE2_NEXT_USE | "
											   "JIT_INSN_VALUE2_LIVE)), "
											   "%d);\n",
					   gensel_first_stack_reg);
			}
			else if((options & (GENSEL_OPT_UNARY |
								GENSEL_OPT_UNARY_BRANCH |
								GENSEL_OPT_UNARY_NOTE)) != 0)
			{
				printf("\t\treg = _jit_regs_load_to_top\n");
				printf("\t\t\t(gen, insn->value1,\n");
				printf("\t\t\t\t(insn->flags & (JIT_INSN_VALUE1_NEXT_USE | "
											   "JIT_INSN_VALUE1_LIVE)), "
											   "%d);\n",
					   gensel_first_stack_reg);
			}
		}
		if((options & (GENSEL_OPT_BINARY_BRANCH |
					   GENSEL_OPT_UNARY_BRANCH)) != 0)
		{
			/* Spill all other registers back to their original positions */
			printf("\t\t_jit_regs_spill_all(gen);\n");
		}
		gensel_output_clause(clause, options);
		printf("\t}\n");
		first = 0;
		clause = clause->next;
	}
}

/*
 * List of opcodes that are supported by the input rules.
 */
static char **supported = 0;
static char **supported_options = 0;
static int num_supported = 0;

/*
 * Add an opcode to the supported list.
 */
static void gensel_add_supported(char *name, char *option)
{
	supported = (char **)realloc
		(supported, (num_supported + 1) * sizeof(char *));
	if(!supported)
	{
		exit(1);
	}
	supported[num_supported] = name;
	supported_options = (char **)realloc
		(supported_options, (num_supported + 1) * sizeof(char *));
	if(!supported_options)
	{
		exit(1);
	}
	supported_options[num_supported++] = option;
}

/*
 * Output the list of supported opcodes.
 */
static void gensel_output_supported(void)
{
	int index;
	for(index = 0; index < num_supported; ++index)
	{
		if(supported_options[index])
		{
			if(supported_options[index][0] == '!')
			{
				printf("#ifndef %s\n", supported_options[index] + 1);
			}
			else
			{
				printf("#ifdef %s\n", supported_options[index]);
			}
			printf("case %s:\n", supported[index]);
			printf("#endif\n");
		}
		else
		{
			printf("case %s:\n", supported[index]);
		}
	}
	printf("\treturn 1;\n\n");
}



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 187 of yacc.c.  */
#line 875 "gen-sel-parser.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 888 "gen-sel-parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   41

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  44
/* YYNRULES -- Number of states.  */
#define YYNSTATES  56

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      31,    32,     2,     2,    30,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    29,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    33,     2,    34,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    11,    17,    20,    22,
      26,    27,    31,    32,    34,    36,    40,    42,    44,    46,
      48,    50,    52,    54,    56,    58,    60,    62,    64,    66,
      69,    75,    76,    78,    80,    84,    86,    88,    90,    92,
      94,    96,    98,   100,   102
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      36,     0,    -1,    -1,    37,    -1,    38,    -1,    37,    38,
      -1,    39,    40,    29,    41,    44,    -1,    28,     3,    -1,
       3,    -1,    39,    30,     3,    -1,    -1,    31,     3,    32,
      -1,    -1,    42,    -1,    43,    -1,    42,    30,    43,    -1,
      16,    -1,    17,    -1,    18,    -1,    19,    -1,    20,    -1,
      21,    -1,    22,    -1,    23,    -1,    24,    -1,    25,    -1,
      26,    -1,    27,    -1,    45,    -1,    44,    45,    -1,    33,
      46,    34,     5,     4,    -1,    -1,    47,    -1,    48,    -1,
      47,    30,    48,    -1,     6,    -1,     7,    -1,     8,    -1,
       9,    -1,    10,    -1,    11,    -1,    12,    -1,    13,    -1,
      14,    -1,    15,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   771,   771,   773,   777,   778,   782,   838,   845,   846,
     862,   863,   867,   868,   872,   873,   877,   878,   879,   880,
     881,   882,   883,   884,   885,   886,   887,   888,   892,   893,
     901,   923,   927,   931,   936,   944,   945,   946,   947,   948,
     949,   950,   951,   952,   953
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"an identifier\"", "\"a code block\"",
  "\"`->'\"", "\"word register\"", "\"long register\"",
  "\"float register\"", "\"immediate value\"", "\"immediate zero value\"",
  "\"immediate signed 8-bit value\"", "\"immediate unsigned 8-bit value\"",
  "\"immediate signed 16-bit value\"",
  "\"immediate unsigned 16-bit value\"", "\"local variable\"",
  "\"`spill_before'\"", "\"`binary'\"", "\"`unary'\"",
  "\"`unary_branch'\"", "\"`binary_branch'\"", "\"`unary_note'\"",
  "\"`binary_note'\"", "\"`ternary'\"", "\"`stack'\"", "\"`only'\"",
  "\"`more_space'\"", "\"`manual'\"", "\"`%inst_type'\"", "':'", "','",
  "'('", "')'", "'['", "']'", "$accept", "Start", "Rules", "Rule",
  "IdentifierList", "IfClause", "Options", "OptionList", "Option",
  "Clauses", "Clause", "Pattern", "Pattern2", "PatternElement", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    58,
      44,    40,    41,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    36,    37,    37,    38,    38,    39,    39,
      40,    40,    41,    41,    42,    42,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    44,    44,
      45,    46,    46,    47,    47,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     5,     2,     1,     3,
       0,     3,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       5,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     8,     0,     0,     3,     4,    10,     7,     1,     5,
       0,     0,     0,     9,     0,    12,    11,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,     0,
      13,    14,    31,     6,    28,     0,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,     0,    32,    33,    29,
      15,     0,     0,     0,    34,    30
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    12,    29,    30,    31,    33,
      34,    46,    47,    48
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -16
static const yytype_int8 yypact[] =
{
      -3,   -16,    23,    27,    -3,   -16,    -7,   -16,   -16,   -16,
      25,    26,     1,   -16,    -1,   -15,   -16,   -16,   -16,   -16,
     -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,     0,
       2,   -16,     7,     0,   -16,   -15,   -16,   -16,   -16,   -16,
     -16,   -16,   -16,   -16,   -16,   -16,     3,     4,   -16,   -16,
     -16,    30,     7,    32,   -16,   -16
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -16,   -16,   -16,    34,   -16,   -16,   -16,   -16,     5,   -16,
       6,   -16,   -16,   -11
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
       1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    10,    11,     2,     7,     8,    13,    14,
      15,    16,    35,    32,    52,    53,    55,    51,     9,    49,
      50,    54
};

static const yytype_uint8 yycheck[] =
{
       3,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    30,    31,    28,     3,     0,     3,     3,
      29,    32,    30,    33,    30,     5,     4,    34,     4,    33,
      35,    52
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    28,    36,    37,    38,    39,     3,     0,    38,
      30,    31,    40,     3,     3,    29,    32,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    41,
      42,    43,    33,    44,    45,    30,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    46,    47,    48,    45,
      43,    34,    30,     5,    48,     4
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 6:
#line 782 "gen-sel-parser.y"
    {
				if((yyvsp[(2) - (5)].name))
				{
					if(((yyvsp[(2) - (5)].name))[0] == '!')
					{
						printf("#ifndef %s\n\n", (yyvsp[(2) - (5)].name) + 1);
					}
					else
					{
						printf("#ifdef %s\n\n", (yyvsp[(2) - (5)].name));
					}
				}
				printf("case %s:\n{\n", (yyvsp[(1) - (5)].name));
				if(((yyvsp[(4) - (5)].options) & GENSEL_OPT_MANUAL) == 0)
				{
					printf("\t%s inst;\n", gensel_inst_type);
				}
				gensel_declare_regs((yyvsp[(5) - (5)].clauses).head, (yyvsp[(4) - (5)].options));
				if(((yyvsp[(4) - (5)].options) & GENSEL_OPT_SPILL_BEFORE) != 0)
				{
					printf("\t_jit_regs_spill_all(gen);\n");
				}
				gensel_output_clauses((yyvsp[(5) - (5)].clauses).head, (yyvsp[(4) - (5)].options));
				if(((yyvsp[(4) - (5)].options) & (GENSEL_OPT_BINARY | GENSEL_OPT_UNARY)) != 0)
				{
					printf("\tif((insn->flags & JIT_INSN_DEST_NEXT_USE) != 0)\n");
					printf("\t{\n");
					printf("\t\t_jit_regs_set_value(gen, reg, insn->dest, 0);\n");
					printf("\t}\n");
					printf("\telse\n");
					printf("\t{\n");
					printf("\t\tint other_reg;\n");
					printf("\t\tif(gen->contents[reg].is_long_start)\n");
					printf("\t\t{\n");
					printf("\t\t\tother_reg = _jit_reg_info[reg].other_reg;\n");
					printf("\t\t}\n");
					printf("\t\telse\n");
					printf("\t\t{\n");
					printf("\t\t\tother_reg = -1;\n");
					printf("\t\t}\n");
					printf("\t\t_jit_gen_spill_reg(gen, reg, other_reg, insn->dest);\n");
					printf("\t\tif(insn->dest->has_global_register)\n");
					printf("\t\t\tinsn->dest->in_global_register = 1;\n");
					printf("\t\telse\n");
					printf("\t\t\tinsn->dest->in_frame = 1;\n");
					printf("\t\t_jit_regs_free_reg(gen, reg, 1);\n");
					printf("\t}\n");
				}
				printf("}\nbreak;\n\n");
				if((yyvsp[(2) - (5)].name))
				{
					printf("#endif /* %s */\n\n", (yyvsp[(2) - (5)].name));
				}
				gensel_free_clauses((yyvsp[(5) - (5)].clauses).head);
				gensel_add_supported((yyvsp[(1) - (5)].name), (yyvsp[(2) - (5)].name));
			}
    break;

  case 7:
#line 838 "gen-sel-parser.y"
    {
				gensel_inst_type = (yyvsp[(2) - (2)].name);
				gensel_new_inst_type = 1;
			}
    break;

  case 8:
#line 845 "gen-sel-parser.y"
    { (yyval.name) = (yyvsp[(1) - (1)].name); }
    break;

  case 9:
#line 846 "gen-sel-parser.y"
    {
				char *result = (char *)malloc(strlen((yyvsp[(1) - (3)].name)) + strlen((yyvsp[(3) - (3)].name)) + 16);
				if(!result)
				{
					exit(1);
				}
				strcpy(result, (yyvsp[(1) - (3)].name));
				strcat(result, ":\ncase ");
				strcat(result, (yyvsp[(3) - (3)].name));
				free((yyvsp[(1) - (3)].name));
				free((yyvsp[(3) - (3)].name));
				(yyval.name) = result;
			}
    break;

  case 10:
#line 862 "gen-sel-parser.y"
    { (yyval.name) = 0; }
    break;

  case 11:
#line 863 "gen-sel-parser.y"
    { (yyval.name) = (yyvsp[(2) - (3)].name); }
    break;

  case 12:
#line 867 "gen-sel-parser.y"
    { (yyval.options) = 0; }
    break;

  case 13:
#line 868 "gen-sel-parser.y"
    { (yyval.options) = (yyvsp[(1) - (1)].options); }
    break;

  case 14:
#line 872 "gen-sel-parser.y"
    { (yyval.options) = (yyvsp[(1) - (1)].options); }
    break;

  case 15:
#line 873 "gen-sel-parser.y"
    { (yyval.options) = (yyvsp[(1) - (3)].options) | (yyvsp[(3) - (3)].options); }
    break;

  case 16:
#line 877 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_OPT_SPILL_BEFORE; }
    break;

  case 17:
#line 878 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_OPT_BINARY; }
    break;

  case 18:
#line 879 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_OPT_UNARY; }
    break;

  case 19:
#line 880 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_OPT_UNARY_BRANCH; }
    break;

  case 20:
#line 881 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_OPT_BINARY_BRANCH; }
    break;

  case 21:
#line 882 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_OPT_UNARY_NOTE; }
    break;

  case 22:
#line 883 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_OPT_BINARY_NOTE; }
    break;

  case 23:
#line 884 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_OPT_TERNARY; }
    break;

  case 24:
#line 885 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_OPT_STACK; }
    break;

  case 25:
#line 886 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_OPT_ONLY; }
    break;

  case 26:
#line 887 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_OPT_MORE_SPACE; }
    break;

  case 27:
#line 888 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_OPT_MANUAL; }
    break;

  case 28:
#line 892 "gen-sel-parser.y"
    { (yyval.clauses) = (yyvsp[(1) - (1)].clauses); }
    break;

  case 29:
#line 893 "gen-sel-parser.y"
    {
				(yyvsp[(1) - (2)].clauses).tail->next = (yyvsp[(2) - (2)].clauses).head;
				(yyval.clauses).head = (yyvsp[(1) - (2)].clauses).head;
				(yyval.clauses).tail = (yyvsp[(2) - (2)].clauses).tail;
			}
    break;

  case 30:
#line 901 "gen-sel-parser.y"
    {
				gensel_clause_t clause;
				int index;
				clause = (gensel_clause_t)malloc(sizeof(struct gensel_clause));
				if(!clause)
				{
					exit(1);
				}
				for(index = 0; index < 8; ++index)
				{
					clause->pattern[index] = (yyvsp[(2) - (5)].pattern).elem[index];
				}
				clause->filename = (yyvsp[(5) - (5)].code).filename;
				clause->linenum = (yyvsp[(5) - (5)].code).linenum;
				clause->code = (yyvsp[(5) - (5)].code).block;
				clause->next = 0;
				(yyval.clauses).head = clause;
				(yyval.clauses).tail = clause;
			}
    break;

  case 31:
#line 923 "gen-sel-parser.y"
    {
				(yyval.pattern).elem[0] = GENSEL_PATT_END;
				(yyval.pattern).size = 0;
			}
    break;

  case 32:
#line 927 "gen-sel-parser.y"
    { (yyval.pattern) = (yyvsp[(1) - (1)].pattern); }
    break;

  case 33:
#line 931 "gen-sel-parser.y"
    {
				(yyval.pattern).elem[0] = (yyvsp[(1) - (1)].options);
				(yyval.pattern).elem[1] = GENSEL_PATT_END;
				(yyval.pattern).size = 1;
			}
    break;

  case 34:
#line 936 "gen-sel-parser.y"
    {
				(yyval.pattern).elem[(yyvsp[(1) - (3)].pattern).size] = (yyvsp[(3) - (3)].options);
				(yyval.pattern).elem[(yyvsp[(1) - (3)].pattern).size + 1] = GENSEL_PATT_END;
				(yyval.pattern).size = (yyvsp[(1) - (3)].pattern).size + 1;
			}
    break;

  case 35:
#line 944 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_PATT_REG; }
    break;

  case 36:
#line 945 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_PATT_LREG; }
    break;

  case 37:
#line 946 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_PATT_FREG; }
    break;

  case 38:
#line 947 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_PATT_IMM; }
    break;

  case 39:
#line 948 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_PATT_IMMZERO; }
    break;

  case 40:
#line 949 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_PATT_IMMS8; }
    break;

  case 41:
#line 950 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_PATT_IMMU8; }
    break;

  case 42:
#line 951 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_PATT_IMMS16; }
    break;

  case 43:
#line 952 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_PATT_IMMU16; }
    break;

  case 44:
#line 953 "gen-sel-parser.y"
    { (yyval.options) = GENSEL_PATT_LOCAL; }
    break;


/* Line 1267 of yacc.c.  */
#line 2433 "gen-sel-parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 956 "gen-sel-parser.y"


#define	COPYRIGHT_MSG	\
" * Copyright (C) 2004  Southern Storm Software, Pty Ltd.\n" \
" *\n" \
" * This file is part of the libjit library.\n" \
" *\n" \
" * The libjit library is free software: you can redistribute it and/or\n" \
" * modify it under the terms of the GNU Lesser General Public License\n" \
" * as published by the Free Software Foundation, either version 2.1 of\n" \
" * the License, or (at your option) any later version.\n" \
" *\n" \
" * The libjit library is distributed in the hope that it will be useful,\n" \
" * but WITHOUT ANY WARRANTY; without even the implied warranty of\n" \
" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU\n" \
" * Lesser General Public License for more details.\n" \
" *\n" \
" * You should have received a copy of the GNU Lesser General Public\n" \
" * License along with the libjit library.  If not, see\n" \
" * <http://www.gnu.org/licenses/>.\n"
 
int main(int argc, char *argv[])
{
	FILE *file;
	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s input.sel >output.slc\n", argv[0]);
		return 1;
	}
	file = fopen(argv[1], "r");
	if(!file)
	{
		perror(argv[1]);
		return 1;
	}
	printf("/%c Automatically generated from %s - DO NOT EDIT %c/\n",
		   '*', argv[1], '*');
	printf("/%c\n%s%c/\n\n", '*', COPYRIGHT_MSG, '*');
	printf("#if defined(JIT_INCLUDE_RULES)\n\n");
	gensel_filename = argv[1];
	gensel_linenum = 1;
	yyrestart(file);
	if(yyparse())
	{
		fclose(file);
		return 1;
	}
	fclose(file);
	printf("#elif defined(JIT_INCLUDE_SUPPORTED)\n\n");
	gensel_output_supported();
	printf("#endif\n");
	return 0;
}

