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
     INTEGER_CONSTANT = 259,
     STRING_CONSTANT = 260,
     REAL_CONSTANT = 261,
     K_AND = 262,
     K_ARRAY = 263,
     K_BEGIN = 264,
     K_CASE = 265,
     K_CATCH = 266,
     K_CONST = 267,
     K_DIV = 268,
     K_DO = 269,
     K_DOWNTO = 270,
     K_ELSE = 271,
     K_END = 272,
     K_EXIT = 273,
     K_FASTCALL = 274,
     K_FINALLY = 275,
     K_FOR = 276,
     K_FORWARD = 277,
     K_FUNCTION = 278,
     K_GOTO = 279,
     K_IF = 280,
     K_IN = 281,
     K_LABEL = 282,
     K_IMPORT = 283,
     K_MOD = 284,
     K_MODULE = 285,
     K_NIL = 286,
     K_NOT = 287,
     K_OF = 288,
     K_OR = 289,
     K_PACKED = 290,
     K_POW = 291,
     K_PROCEDURE = 292,
     K_PROGRAM = 293,
     K_RECORD = 294,
     K_REPEAT = 295,
     K_SET = 296,
     K_SHL = 297,
     K_SHR = 298,
     K_SIZEOF = 299,
     K_STDCALL = 300,
     K_THEN = 301,
     K_THROW = 302,
     K_TO = 303,
     K_TRY = 304,
     K_TYPE = 305,
     K_UNTIL = 306,
     K_VAR = 307,
     K_VA_ARG = 308,
     K_WITH = 309,
     K_WHILE = 310,
     K_XOR = 311,
     K_NE = 312,
     K_LE = 313,
     K_GE = 314,
     K_ASSIGN = 315,
     K_DOT_DOT = 316
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define INTEGER_CONSTANT 259
#define STRING_CONSTANT 260
#define REAL_CONSTANT 261
#define K_AND 262
#define K_ARRAY 263
#define K_BEGIN 264
#define K_CASE 265
#define K_CATCH 266
#define K_CONST 267
#define K_DIV 268
#define K_DO 269
#define K_DOWNTO 270
#define K_ELSE 271
#define K_END 272
#define K_EXIT 273
#define K_FASTCALL 274
#define K_FINALLY 275
#define K_FOR 276
#define K_FORWARD 277
#define K_FUNCTION 278
#define K_GOTO 279
#define K_IF 280
#define K_IN 281
#define K_LABEL 282
#define K_IMPORT 283
#define K_MOD 284
#define K_MODULE 285
#define K_NIL 286
#define K_NOT 287
#define K_OF 288
#define K_OR 289
#define K_PACKED 290
#define K_POW 291
#define K_PROCEDURE 292
#define K_PROGRAM 293
#define K_RECORD 294
#define K_REPEAT 295
#define K_SET 296
#define K_SHL 297
#define K_SHR 298
#define K_SIZEOF 299
#define K_STDCALL 300
#define K_THEN 301
#define K_THROW 302
#define K_TO 303
#define K_TRY 304
#define K_TYPE 305
#define K_UNTIL 306
#define K_VAR 307
#define K_VA_ARG 308
#define K_WITH 309
#define K_WHILE 310
#define K_XOR 311
#define K_NE 312
#define K_LE 313
#define K_GE 314
#define K_ASSIGN 315
#define K_DOT_DOT 316




/* Copy the first part of user declarations.  */
#line 1 "dpas-parser.y"

/*
 * dpas-parser.y - Bison grammar for the Dynamic Pascal language.
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

#include "dpas-internal.h"
#include <jit/jit-dump.h>
#include <config.h>
#ifdef HAVE_STDLIB_H
	#include <stdlib.h>
#endif
#ifdef HAVE_STDARG_H
	#include <stdarg.h>
#elif HAVE_VARARGS_H
	#include <varargs.h>
#endif

/*
 * Imports from the lexical analyser.
 */
extern int yylex(void);
#ifdef YYTEXT_POINTER
extern char *yytext;
#else
extern char yytext[];
#endif

/*
 * Error reporting flag.
 */
int dpas_error_reported = 0;

/*
 * Function dumping flag.
 */
int dpas_dump_functions = 0;

/*
 * Report error messages from the parser.
 */
static void yyerror(char *msg)
{
	char *text = yytext;
	char *newmsg;
	int posn, outposn;
	dpas_error_reported = 1;
	if(!jit_strcmp(msg, "parse error") || !jit_strcmp(msg, "syntax error"))
	{
		/* This error is pretty much useless at telling the user
		   what is happening.  Try to print a better message
		   based on the current input token */
	simpleError:
		if(text && *text != '\0')
		{
			fprintf(stderr, "%s:%ld: parse error at or near `%s'\n",
					dpas_filename, dpas_linenum, text);
		}
		else
		{
			fprintf(stderr, "%s:%ld: parse error\n",
					dpas_filename, dpas_linenum);
		}
	}
	else if(!jit_strncmp(msg, "parse error, expecting `", 24))
	{
		/* We have to quote the token names in the "%token" declarations
		   within yacc grammars so that byacc doesn't mess up the output.
		   But the quoting causes Bison to output quote characters in
		   error messages which look awful.  This code attempts to fix
		   things up */
		newmsg = jit_strdup(msg);
	expectingError:
		if(newmsg)
		{
			posn = 0;
			outposn = 0;
			while(newmsg[posn] != '\0')
			{
				if(newmsg[posn] == '`')
				{
					if(newmsg[posn + 1] == '"' && newmsg[posn + 2] == '`')
					{
						/* Convert <`"`> into <`> */
						posn += 2;
						newmsg[outposn++] = '`';
					}
					else if(newmsg[posn + 1] == '"')
					{
						/* Convert <`"> into <> */
						++posn;
					}
					else if(newmsg[posn + 1] == '`' ||
					        newmsg[posn + 1] == '\'')
					{
						/* Convert <``> or <`'> into <`> */
						++posn;
						newmsg[outposn++] = '`';
					}
					else
					{
						/* Ordinary <`> on its own */
						newmsg[outposn++] = '`';
					}
				}
				else if(newmsg[posn] == '\\')
				{
					/* Ignore backslashes in the input */
				}
				else if(newmsg[posn] == '"' && newmsg[posn + 1] == '\'')
				{
					/* Convert <"'> into <> */
					++posn;
				}
				else if(newmsg[posn] == '\'' && newmsg[posn + 1] == '"' &&
				        newmsg[posn + 2] == '\'')
				{
					/* Convert <'"'> into <'> */
					posn += 2;
					newmsg[outposn++] = '\'';
				}
				else if(newmsg[posn] == '\'' && newmsg[posn + 1] == '\'')
				{
					/* Convert <''> into <'> */
					++posn;
					newmsg[outposn++] = '\'';
				}
				else if(newmsg[posn] == ' ' && newmsg[posn + 1] == '\'')
				{
					/*  bison 1.75 - <'> following a space becomes <`> */
					++posn;
					newmsg[outposn++] = ' ';
					newmsg[outposn++] = '`';
				}
				else if(newmsg[posn] == '"')
				{
					/* Ignore quotes - bison 1.75 */
				}
				else
				{
					/* Ordinary character */
					newmsg[outposn++] = newmsg[posn];
				}
				++posn;
			}
			newmsg[outposn] = '\0';
			if(text && *text != '\0')
			{
				fprintf(stderr, "%s:%ld: %s, at or near `%s'\n",
						dpas_filename, dpas_linenum, newmsg, text);
			}
			else
			{
				fprintf(stderr, "%s:%ld: %s\n",
						dpas_filename, dpas_linenum, newmsg);
			}
			jit_free(newmsg);
		}
		else
		{
			if(text && *text != '\0')
			{
				fprintf(stderr, "%s:%ld: %s at or near `%s'\n",
						dpas_filename, dpas_linenum, msg, text);
			}
			else
			{
				fprintf(stderr, "%s:%ld: %s\n",
						dpas_filename, dpas_linenum, msg);
			}
		}
	}
	else if(!jit_strncmp(msg, "parse error, unexpected ", 24))
	{
		/* The error probably has the form "parse error, unexpected ...,
		   expecting ..." - strip out the "unexpected" part */
		posn = 24;
		while(msg[posn] != '\0' &&
			  jit_strncmp(msg + posn, ", expecting ", 12) != 0)
		{
			++posn;
		}
		if(msg[posn] == '\0')
		{
			goto simpleError;
		}
		newmsg = (char *)jit_malloc(jit_strlen(msg) + 1);
		if(!newmsg)
		{
			goto defaultError;
		}
		jit_strcpy(newmsg, "parse error, expecting ");
		jit_strcat(newmsg, msg + posn + 12);
		goto expectingError;
	}
	else
	{
		/* The parser has probably included information as to what
		   is expected in this context, so report that */
	defaultError:
		if(text && *text != '\0')
		{
			fprintf(stderr, "%s:%ld: %s at or near `%s'\n",
					dpas_filename, dpas_linenum, msg, text);
		}
		else
		{
			fprintf(stderr, "%s:%ld: %s\n",
					dpas_filename, dpas_linenum, msg);
		}
	}
}

void dpas_error(const char *format, ...)
{
	va_list va;
#ifdef HAVE_STDARG_H
	va_start(va, format);
#else
	va_start(va);
#endif
	fprintf(stderr, "%s:%ld: ", dpas_filename, dpas_linenum);
	vfprintf(stderr, format, va);
	putc('\n', stderr);
	va_end(va);
	dpas_error_reported = 1;
}

void dpas_warning(const char *format, ...)
{
	va_list va;
#ifdef HAVE_STDARG_H
	va_start(va, format);
#else
	va_start(va);
#endif
	fprintf(stderr, "%s:%ld: warning: ", dpas_filename, dpas_linenum);
	vfprintf(stderr, format, va);
	putc('\n', stderr);
	va_end(va);
}

void dpas_error_on_line(const char *filename, long linenum,
                        const char *format, ...)
{
	va_list va;
#ifdef HAVE_STDARG_H
	va_start(va, format);
#else
	va_start(va);
#endif
	fprintf(stderr, "%s:%ld: ", filename, linenum);
	vfprintf(stderr, format, va);
	putc('\n', stderr);
	va_end(va);
	dpas_error_reported = 1;
}

static void dpas_undeclared(const char *name)
{
	dpas_error("`%s' is not declared in the current scope", name);
}

static void dpas_redeclared(const char *name, dpas_scope_item_t item)
{
	dpas_error("`%s' is already declared in the current scope", name);
	dpas_error_on_line(dpas_scope_item_filename(item),
					   dpas_scope_item_linenum(item),
					   "previous declaration of `%s' here", name);
}

/*
 * Add an item to a list of identifiers.
 */
static void identifier_list_add(char ***list, int *len, char *name)
{
	char **new_list = (char **)jit_realloc(*list, sizeof(char *) * (*len + 1));
	if(!new_list)
	{
		dpas_out_of_memory();
	}
	new_list[*len] = name;
	++(*len);
	*list = new_list;
}

/*
 * Free the contents of an identifier list.
 */
static void identifier_list_free(char **list, int len)
{
	int posn;
	for(posn = 0; posn < len; ++posn)
	{
		jit_free(list[posn]);
	}
	jit_free(list);
}

/*
 * Determine if an identifier list contains a specific item.
 */
static int identifier_list_contains(char **list, int len, const char *name)
{
	int posn;
	for(posn = 0; posn < len; ++posn)
	{
		if(list[posn] && !jit_stricmp(list[posn], name))
		{
			return 1;
		}
	}
	return 0;
}

/*
 * Add an item to a list of types.
 */
static void type_list_add(jit_type_t **list, int *len, jit_type_t type)
{
	jit_type_t *new_list = (jit_type_t *)
		jit_realloc(*list, sizeof(jit_type_t) * (*len + 1));
	if(!new_list)
	{
		dpas_out_of_memory();
	}
	new_list[*len] = type;
	++(*len);
	*list = new_list;
}

/*
 * Initialize a parameter list.
 */
static void parameter_list_init(dpas_params *list)
{
	list->names = 0;
	list->types = 0;
	list->len = 0;
	list->abi = jit_abi_cdecl;
}

/*
 * Add an item to a list of parameters.
 */
static void parameter_list_add(dpas_params *list, char *name, jit_type_t type)
{
	char **new_names = (char **)
		jit_realloc(list->names, sizeof(char *) * (list->len + 1));
	jit_type_t *new_types = (jit_type_t *)
		jit_realloc(list->types, sizeof(jit_type_t) * (list->len + 1));
	if(!new_names || !new_types)
	{
		dpas_out_of_memory();
	}
	new_names[list->len] = name;
	new_types[list->len] = type;
	++(list->len);
	list->names = new_names;
	list->types = new_types;
}

/*
 * Free the contents of a parameter list.
 */
static void parameter_list_free(dpas_params *list)
{
	int posn;
	for(posn = 0; posn < list->len; ++posn)
	{
		jit_free(list->names[posn]);
		jit_type_free(list->types[posn]);
	}
	jit_free(list->names);
	jit_free(list->types);
}

/*
 * Determine if a parameter list contains a specific item.
 */
static int parameter_list_contains(dpas_params *list, const char *name)
{
	int posn;
	for(posn = 0; posn < list->len; ++posn)
	{
		if(list->names[posn] && !jit_stricmp(list->names[posn], name))
		{
			return 1;
		}
	}
	return 0;
}

/*
 * Create a new parameter list.
 */
static void parameter_list_create(dpas_params *list, char **names,
								  int num_names, jit_type_t type)
{
	char **temp = names;
	parameter_list_init(list);
	while(num_names > 0)
	{
		parameter_list_add(list, temp[0], jit_type_copy(type));
		--num_names;
		++temp;
	}
	if(names)
	{
		jit_free(names);
	}
}

/*
 * Merge two parameter lists into one.
 */
static void parameter_list_merge(dpas_params *list1, dpas_params *list2)
{
	int posn;
	char *name;
	for(posn = 0; posn < list2->len; ++posn)
	{
		name = list2->names[posn];
		if(name && parameter_list_contains(list1, name))
		{
			dpas_error("`%s' used twice in a parameter or field list", name);
			jit_free(name);
			name = 0;
		}
		parameter_list_add(list1, name, list2->types[posn]);
	}
	jit_free(list2->names);
	jit_free(list2->types);
}

/*
 * Add an item to an expression list.
 */
static void expression_list_add
	(dpas_semvalue **list, int *len, dpas_semvalue value)
{
	dpas_semvalue *new_list = (dpas_semvalue *)
		jit_realloc(*list, sizeof(dpas_semvalue) * (*len + 1));
	if(!new_list)
	{
		dpas_out_of_memory();
	}
	new_list[*len] = value;
	++(*len);
	*list = new_list;
}

/*
 * Free an expression list.
 */
static void expression_list_free(dpas_semvalue *list, int len)
{
	jit_free(list);
}

/*
 * Invoke a procedure or function.
 */
static dpas_semvalue invoke_procedure
	(jit_function_t func_value, const char *name, jit_type_t signature,
	 jit_value_t indirect_value, dpas_semvalue *args, int num_args)
{
	jit_function_t func = dpas_current_function();
	dpas_semvalue rvalue;
	jit_type_t type;
	jit_value_t return_value;
	jit_value_t *value_args;
	jit_type_t param_type;
	jit_type_t var_type;
	unsigned int param;
	int error;

	/* Validate the parameters (TODO: vararg function calls) */
	if(num_args != (int)jit_type_num_params(signature))
	{
		dpas_error("incorrect number of parameters to procedure or function");
		dpas_sem_set_error(rvalue);
		return rvalue;
	}
	error = 0;
	if(num_args > 0)
	{
		value_args = (jit_value_t *)jit_malloc(sizeof(jit_value_t) * num_args);
		if(!value_args)
		{
			dpas_out_of_memory();
		}
		for(param = 0; param < (unsigned int)num_args; ++param)
		{
			param_type = jit_type_get_param(signature, param);
			var_type = dpas_type_is_var(param_type);
			if(var_type)
			{
				/* TODO: type checking */
				if(dpas_sem_is_lvalue_ea(args[param]))
				{
					value_args[param] = dpas_sem_get_value(args[param]);
				}
				else if(dpas_sem_is_lvalue(args[param]))
				{
					value_args[param] = jit_insn_address_of
						(func, dpas_sem_get_value(args[param]));
					if(!(value_args[param]))
					{
						dpas_out_of_memory();
					}
				}
				else
				{
					dpas_error("invalid value for parameter %d",
							   (int)(param + 1));
					error = 1;
				}
			}
			else
			{
				/* TODO: type checking */
				if(dpas_sem_is_rvalue(args[param]))
				{
					value_args[param] = dpas_sem_get_value
						(dpas_lvalue_to_rvalue(args[param]));
				}
				else
				{
					dpas_error("invalid value for parameter %d",
							   (int)(param + 1));
					error = 1;
				}
			}
		}
	}
	else
	{
		value_args = 0;
	}
	if(error)
	{
		jit_free(value_args);
		dpas_sem_set_error(rvalue);
		return rvalue;
	}

	/* Call the specified procedure or function */
	if(func_value)
	{
		return_value = jit_insn_call
			(func, name, func_value, signature,
			 value_args, (unsigned int)num_args, 0);
	}
	else
	{
		return_value = jit_insn_call_indirect
			(func, indirect_value, signature,
			 value_args, (unsigned int)num_args, 0);
	}
	if(!return_value)
	{
		dpas_out_of_memory();
	}
	jit_free(value_args);

	/* Construct a semantic value object for the return value */
	type = jit_type_get_return(signature);
	if(type == jit_type_void)
	{
		dpas_sem_set_void(rvalue);
	}
	else
	{
		dpas_sem_set_rvalue(rvalue, type, return_value);
	}
	return rvalue;
}

static int throw_builtin_exception(jit_function_t func, int exception_type)
{
	jit_type_t signature;
	jit_type_t param_types[1];
	jit_value_t param_values[1];

	/* Call the "jit_exception_builtin" function to report the exception */
	param_types[0] = jit_type_int;
	signature = jit_type_create_signature
		(jit_abi_cdecl, jit_type_void, param_types, 1, 1);
	if(!signature)
	{
		return 0;
	}

	param_values[0] = jit_value_create_nint_constant(func, jit_type_int, exception_type);
	if(!param_values[0])
	{
		return 0;
	}
	jit_insn_call_native
		(func, "jit_exception_builtin",
		 (void *)jit_exception_builtin, signature, param_values, 1,
		 JIT_CALL_NORETURN);
	jit_type_free(signature);

	return 1;
}

/*
 * Handle a numeric binary operator.
 */
#define	handle_binary(name,func,arg1,arg2)	\
		do { \
			if(!dpas_sem_is_rvalue(arg1) || \
			   !dpas_type_is_numeric(dpas_sem_get_type(arg2)) || \
			   !dpas_sem_is_rvalue(arg1) || \
			   !dpas_type_is_numeric(dpas_sem_get_type(arg2))) \
			{ \
				if(!dpas_sem_is_error(arg1) && !dpas_sem_is_error(arg2)) \
				{ \
					dpas_error("invalid operands to binary `" name "'"); \
				} \
				dpas_sem_set_error(yyval.semvalue); \
			} \
			else \
			{ \
				jit_value_t value; \
				value = func \
					(dpas_current_function(), \
					 dpas_sem_get_value(dpas_lvalue_to_rvalue(arg1)), \
					 dpas_sem_get_value(dpas_lvalue_to_rvalue(arg2))); \
				dpas_sem_set_rvalue \
					(yyval.semvalue, jit_value_get_type(value), value); \
			} \
		} while (0)

/*
 * Handle an integer binary operator.
 */
#define	handle_integer_binary(name,func,arg1,arg2)	\
		do { \
			if(!dpas_sem_is_rvalue(arg1) || \
			   !dpas_type_is_integer(dpas_sem_get_type(arg2)) || \
			   !dpas_sem_is_rvalue(arg1) || \
			   !dpas_type_is_integer(dpas_sem_get_type(arg2))) \
			{ \
				if(!dpas_sem_is_error(arg1) && !dpas_sem_is_error(arg2)) \
				{ \
					dpas_error("invalid operands to binary `" name "'"); \
				} \
				dpas_sem_set_error(yyval.semvalue); \
			} \
			else \
			{ \
				jit_value_t value; \
				value = func \
					(dpas_current_function(), \
					 dpas_sem_get_value(dpas_lvalue_to_rvalue(arg1)), \
					 dpas_sem_get_value(dpas_lvalue_to_rvalue(arg2))); \
				dpas_sem_set_rvalue \
					(yyval.semvalue, jit_value_get_type(value), value); \
			} \
		} while (0)

/*
 * Handle a boolean binary operator.
 */
#define	handle_boolean_binary(name,func,arg1,arg2)	\
		do { \
			if(!dpas_sem_is_rvalue(arg1) || \
			   !dpas_type_is_numeric(dpas_sem_get_type(arg2)) || \
			   !dpas_sem_is_rvalue(arg1) || \
			   !dpas_type_is_numeric(dpas_sem_get_type(arg2))) \
			{ \
				if(!dpas_sem_is_error(arg1) && !dpas_sem_is_error(arg2)) \
				{ \
					dpas_error("invalid operands to binary `" name "'"); \
				} \
				dpas_sem_set_error(yyval.semvalue); \
			} \
			else \
			{ \
				jit_value_t value; \
				value = func \
					(dpas_current_function(), \
					 dpas_sem_get_value(dpas_lvalue_to_rvalue(arg1)), \
					 dpas_sem_get_value(dpas_lvalue_to_rvalue(arg2))); \
				dpas_sem_set_rvalue \
					(yyval.semvalue, dpas_type_boolean, value); \
			} \
		} while (0)

/*
 * Handle a comparison binary operator.
 */
#define	handle_compare_binary(name,func,arg1,arg2)	\
		do { \
			if(dpas_sem_is_rvalue(arg1) && \
			   jit_type_is_pointer(dpas_sem_get_type(arg1)) && \
			   dpas_sem_is_rvalue(arg2) && \
			   jit_type_is_pointer(dpas_sem_get_type(arg2))) \
			{ \
				jit_value_t value; \
				value = func \
					(dpas_current_function(), \
					 dpas_sem_get_value(dpas_lvalue_to_rvalue(arg1)), \
					 dpas_sem_get_value(dpas_lvalue_to_rvalue(arg2))); \
				dpas_sem_set_rvalue \
					(yyval.semvalue, dpas_type_boolean, value); \
			} \
			else \
			{ \
				handle_boolean_binary(name, func, arg1, arg2); \
			} \
		} while (0)

/*
 * Definition of the loop stack.
 */
typedef struct
{
	jit_label_t		expr_label;
	jit_label_t		top_label;
	jit_label_t		exit_label;

} dpas_loop_info;
static dpas_loop_info *loop_stack = 0;
static int loop_stack_size = 0;
static int loop_stack_max = 0;

/*
 * Push an entry onto the loop stack.
 */
static void push_loop
	(jit_label_t expr_label, jit_label_t top_label, jit_label_t exit_label)
{
	dpas_loop_info *new_stack;
	if(loop_stack_size >= loop_stack_max)
	{
		new_stack = (dpas_loop_info *)jit_realloc
			(loop_stack, sizeof(dpas_loop_info) * (loop_stack_size + 1));
		if(!new_stack)
		{
			dpas_out_of_memory();
		}
		loop_stack = new_stack;
		++loop_stack_max;
	}
	loop_stack[loop_stack_size].expr_label = expr_label;
	loop_stack[loop_stack_size].top_label = top_label;
	loop_stack[loop_stack_size].exit_label = exit_label;
	++loop_stack_size;
}

/*
 * Definition of the "if" stack.
 */
static jit_label_t *if_stack = 0;
static int if_stack_size = 0;
static int if_stack_max = 0;

/*
 * Push an entry onto the loop stack.
 */
static void push_if(jit_label_t end_label)
{
	jit_label_t *new_stack;
	if(if_stack_size >= if_stack_max)
	{
		new_stack = (jit_label_t *)jit_realloc
			(if_stack, sizeof(jit_label_t) * (if_stack_size + 1));
		if(!new_stack)
		{
			dpas_out_of_memory();
		}
		if_stack = new_stack;
		++if_stack_max;
	}
	if_stack[if_stack_size] = end_label;
	++if_stack_size;
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
#line 805 "dpas-parser.y"
{
	char		   *name;
	struct
	{
		jit_ulong	value;
		jit_type_t	type;
	}				int_const;
	jit_nfloat		real_const;
	jit_constant_t	const_value;
	jit_type_t		type;
	struct
	{
		char	  **list;
		int			len;
	}				id_list;
	struct
	{
		jit_type_t *list;
		int			len;
	}				type_list;
	dpas_params		parameters;
	struct
	{
		char	   *name;
		jit_type_t	type;
	}				procedure;
	struct
	{
		jit_type_t	type;
		dpas_params	bounds;
	}				param_type;
	dpas_semvalue	semvalue;
	struct
	{
		dpas_semvalue *exprs;
		int			len;
	}				expr_list;
	int				direction;
	jit_abi_t		abi;
}
/* Line 187 of yacc.c.  */
#line 1060 "dpas-parser.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 1073 "dpas-parser.c"

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
#define YYLAST   611

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  93
/* YYNRULES -- Number of rules.  */
#define YYNRULES  212
/* YYNRULES -- Number of states.  */
#define YYNSTATES  415

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   316

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    77,     2,
      63,    64,    75,    73,    66,    74,    62,    76,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    68,    65,
      71,    67,    72,     2,    78,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    69,     2,    70,    79,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    15,    19,    26,    30,    31,    35,
      37,    41,    43,    45,    47,    51,    54,    60,    61,    65,
      67,    71,    73,    74,    77,    79,    82,    87,    88,    91,
      93,    96,   101,   102,   105,   107,   110,   115,   116,   118,
     121,   125,   130,   134,   136,   140,   141,   143,   144,   149,
     151,   153,   155,   157,   159,   164,   168,   174,   175,   180,
     186,   187,   189,   191,   193,   197,   201,   206,   208,   210,
     212,   214,   222,   229,   231,   235,   241,   243,   247,   251,
     253,   255,   258,   261,   263,   265,   267,   269,   271,   273,
     278,   281,   283,   285,   287,   288,   292,   297,   301,   305,
     306,   312,   314,   315,   320,   321,   322,   329,   330,   337,
     338,   346,   348,   350,   352,   357,   359,   363,   367,   369,
     373,   375,   379,   386,   387,   394,   395,   399,   401,   405,
     409,   413,   417,   421,   425,   429,   431,   435,   437,   440,
     443,   445,   449,   453,   457,   459,   463,   467,   471,   475,
     479,   483,   487,   491,   493,   497,   499,   501,   505,   508,
     511,   514,   517,   521,   526,   531,   536,   545,   547,   552,
     556,   559,   561,   563,   565,   568,   570,   574,   578,   585,
     589,   593,   596,   598,   602,   604,   605,   607,   610,   614,
     619,   621,   624,   626,   630,   634,   636,   643,   649,   651,
     653,   657,   663,   665,   669,   671,   674,   677,   679,   681,
     683,   685,   687
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      81,     0,    -1,    82,    83,    85,    62,    -1,    38,    86,
      63,    87,    64,    65,    -1,    38,    86,    65,    -1,    30,
      86,    63,    87,    64,    65,    -1,    30,    86,    65,    -1,
      -1,    28,    84,    65,    -1,    86,    -1,    84,    66,    86,
      -1,    88,    -1,     3,    -1,    86,    -1,    87,    66,    86,
      -1,    89,   104,    -1,    90,    93,    96,    99,   102,    -1,
      -1,    27,    91,    65,    -1,    92,    -1,    91,    66,    92,
      -1,     4,    -1,    -1,    12,    94,    -1,    95,    -1,    94,
      95,    -1,    86,    67,   170,    65,    -1,    -1,    50,    97,
      -1,    98,    -1,    97,    98,    -1,    86,    67,   157,    65,
      -1,    -1,    52,   100,    -1,   101,    -1,   100,   101,    -1,
      87,    68,   157,    65,    -1,    -1,   103,    -1,   106,    65,
      -1,   103,   106,    65,    -1,     9,   121,   105,    17,    -1,
       9,   105,    17,    -1,    17,    -1,     9,     1,    17,    -1,
      -1,    65,    -1,    -1,   108,    65,   107,   109,    -1,   111,
      -1,   112,    -1,    88,    -1,   110,    -1,    22,    -1,    28,
      63,     5,    64,    -1,    37,    86,   113,    -1,    23,    86,
     113,    68,   156,    -1,    -1,    63,   115,    64,   114,    -1,
      63,   115,    65,    61,    64,    -1,    -1,    19,    -1,    45,
      -1,   116,    -1,   115,    65,   116,    -1,    87,    68,   117,
      -1,    52,    87,    68,   117,    -1,   111,    -1,   112,    -1,
     156,    -1,   118,    -1,    35,     8,    69,   120,    70,    33,
     156,    -1,     8,    69,   119,    70,    33,   117,    -1,   120,
      -1,   119,    65,   120,    -1,    86,    61,    86,    68,   156,
      -1,   122,    -1,   121,    65,   122,    -1,    92,    68,   123,
      -1,   123,    -1,   126,    -1,   155,   124,    -1,    24,    92,
      -1,   125,    -1,   127,    -1,   131,    -1,   134,    -1,   136,
      -1,   140,    -1,    54,   144,    14,   122,    -1,    47,   148,
      -1,    47,    -1,   145,    -1,    18,    -1,    -1,    63,   149,
      64,    -1,     9,   121,   105,    17,    -1,     9,     1,    17,
      -1,   155,    60,   148,    -1,    -1,    25,   138,    46,   128,
     129,    -1,   122,    -1,    -1,   122,    16,   130,   122,    -1,
      -1,    -1,    55,   132,   138,    14,   133,   122,    -1,    -1,
      40,   135,   121,   105,    51,   138,    -1,    -1,    21,   126,
     139,   148,    14,   137,   122,    -1,   148,    -1,    48,    -1,
      15,    -1,    10,   148,    33,   141,    -1,   142,    -1,   141,
      65,   142,    -1,   143,    68,   122,    -1,   170,    -1,   143,
      66,   170,    -1,   155,    -1,   144,    66,   155,    -1,    49,
     121,   105,   146,   147,    17,    -1,    -1,    11,    86,    68,
     157,   121,   105,    -1,    -1,    20,   121,   105,    -1,   150,
      -1,   150,    67,   150,    -1,   150,    57,   150,    -1,   150,
      71,   150,    -1,   150,    72,   150,    -1,   150,    58,   150,
      -1,   150,    59,   150,    -1,   150,    26,   150,    -1,   148,
      -1,   149,    66,   148,    -1,   151,    -1,    73,   151,    -1,
      74,   151,    -1,   152,    -1,   151,    73,   152,    -1,   151,
      74,   152,    -1,   151,    34,   152,    -1,   153,    -1,   152,
      75,   153,    -1,   152,    76,   153,    -1,   152,    13,   153,
      -1,   152,    29,   153,    -1,   152,     7,   153,    -1,   152,
      56,   153,    -1,   152,    42,   153,    -1,   152,    43,   153,
      -1,   154,    -1,   153,    36,   154,    -1,   155,    -1,   172,
      -1,    69,   149,    70,    -1,    69,    70,    -1,    32,   154,
      -1,    77,   154,    -1,    78,   154,    -1,    63,   148,    64,
      -1,   155,    63,   149,    64,    -1,    53,    63,   156,    64,
      -1,    44,    63,   155,    64,    -1,    63,    25,   148,    46,
     148,    16,   148,    64,    -1,    86,    -1,   155,    69,   149,
      70,    -1,   155,    62,    86,    -1,   155,    79,    -1,    86,
      -1,   158,    -1,   159,    -1,    35,   159,    -1,   156,    -1,
      63,    87,    64,    -1,   170,    61,   170,    -1,     8,    69,
     160,    70,    33,   157,    -1,    39,   162,    17,    -1,    41,
      33,   157,    -1,    79,    86,    -1,   161,    -1,   160,    66,
     161,    -1,   158,    -1,    -1,   163,    -1,   163,    65,    -1,
     163,    65,   165,    -1,   163,    65,   165,    65,    -1,   165,
      -1,   165,    65,    -1,   164,    -1,   163,    65,   164,    -1,
      87,    68,   157,    -1,   108,    -1,    10,    86,    68,   156,
      33,   166,    -1,    10,    68,   156,    33,   166,    -1,   167,
      -1,   168,    -1,   167,    65,   168,    -1,   169,    68,    63,
     162,    64,    -1,   170,    -1,   169,    66,   170,    -1,   171,
      -1,    73,   171,    -1,    74,   171,    -1,   172,    -1,    86,
      -1,     4,    -1,     6,    -1,     5,    -1,    31,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   960,   960,   964,   968,   971,   978,   983,   985,   989,
     993,  1000,  1041,  1045,  1050,  1070,  1074,  1078,  1080,  1084,
    1085,  1089,  1092,  1094,  1098,  1099,  1103,  1120,  1122,  1130,
    1131,  1135,  1168,  1170,  1174,  1175,  1179,  1229,  1231,  1235,
    1236,  1240,  1241,  1242,  1243,  1246,  1248,  1256,  1256,  1364,
    1365,  1369,  1370,  1374,  1375,  1379,  1398,  1417,  1418,  1422,
    1429,  1430,  1431,  1435,  1436,  1443,  1459,  1485,  1489,  1496,
    1500,  1504,  1508,  1516,  1517,  1524,  1554,  1555,  1559,  1560,
    1564,  1565,  1599,  1603,  1604,  1605,  1606,  1607,  1608,  1609,
    1613,  1617,  1621,  1622,  1641,  1642,  1646,  1647,  1651,  1826,
    1826,  1857,  1858,  1858,  1885,  1906,  1885,  1954,  1954,  1995,
    1995,  2176,  2183,  2184,  2188,  2195,  2196,  2200,  2204,  2205,
    2209,  2210,  2214,  2220,  2222,  2225,  2227,  2235,  2236,  2239,
    2242,  2245,  2248,  2251,  2254,  2260,  2265,  2272,  2273,  2288,
    2310,  2311,  2314,  2317,  2387,  2388,  2391,  2396,  2399,  2402,
    2469,  2472,  2475,  2481,  2482,  2488,  2489,  2494,  2499,  2504,
    2530,  2563,  2596,  2597,  2652,  2657,  2678,  2686,  2783,  2982,
    3047,  3099,  3122,  3123,  3124,  3128,  3129,  3168,  3204,  3207,
    3224,  3236,  3280,  3285,  3292,  3314,  3315,  3316,  3317,  3321,
    3325,  3326,  3330,  3331,  3338,  3342,  3349,  3354,  3362,  3371,
    3376,  3383,  3404,  3405,  3413,  3414,  3428,  3466,  3467,  3492,
    3511,  3515,  3522
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"an identifier\"",
  "\"an integer value\"", "\"a string literal\"",
  "\"a floating point value\"", "\"`and'\"", "\"`array'\"", "\"`begin'\"",
  "\"`case'\"", "\"`catch'\"", "\"`const'\"", "\"`div'\"", "\"`do'\"",
  "\"`downto'\"", "\"`else'\"", "\"`end'\"", "\"`exit'\"",
  "\"`fastcall'\"", "\"`finally'\"", "\"`for'\"", "\"`forward'\"",
  "\"`function'\"", "\"`goto'\"", "\"`if'\"", "\"`in'\"", "\"`label'\"",
  "\"`import'\"", "\"`mod'\"", "\"`module'\"", "\"`nil'\"", "\"`not'\"",
  "\"`of'\"", "\"`or'\"", "\"`packed'\"", "\"`pow'\"", "\"`procedure'\"",
  "\"`program'\"", "\"`record'\"", "\"`repeat'\"", "\"`set'\"",
  "\"`shl'\"", "\"`shr'\"", "\"`sizeof'\"", "\"`stdcall'\"", "\"`then'\"",
  "\"`throw'\"", "\"`to'\"", "\"`try'\"", "\"`type'\"", "\"`until'\"",
  "\"`var'\"", "\"`va_arg'\"", "\"`with'\"", "\"`while'\"", "\"`xor'\"",
  "\"`<>'\"", "\"`<='\"", "\"`>='\"", "\"`:='\"", "\"`..'\"", "'.'", "'('",
  "')'", "';'", "','", "'='", "':'", "'['", "']'", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'&'", "'@'", "'^'", "$accept", "Program",
  "ProgramHeading", "ImportDeclarationPart", "ImportDeclarations",
  "ProgramBlock", "Identifier", "IdentifierList", "Block",
  "DeclarationPart", "LabelDeclarationPart", "LabelList", "Label",
  "ConstantDefinitionPart", "ConstantDefinitionList", "ConstantDefinition",
  "TypeDefinitionPart", "TypeDefinitionList", "TypeDefinition",
  "VariableDeclarationPart", "VariableDeclarationList",
  "VariableDeclaration", "ProcedureAndFunctionDeclarationPart",
  "ProcedureOrFunctionList", "StatementPart", "OptSemi",
  "ProcedureOrFunctionDeclaration", "@1", "ProcedureOrFunctionHeading",
  "Body", "Directive", "ProcedureHeading", "FunctionHeading",
  "FormalParameterList", "OptAbi", "FormalParameterSections",
  "FormalParameterSection", "ParameterType", "ConformantArray",
  "BoundSpecificationList", "BoundSpecification", "StatementSequence",
  "Statement", "InnerStatement", "ActualParameters", "CompoundStatement",
  "AssignmentStatement", "IfStatement", "@2", "IfTail", "@3",
  "WhileStatement", "@4", "@5", "RepeatStatement", "@6", "ForStatement",
  "@7", "BooleanExpression", "Direction", "CaseStatement", "CaseLimbList",
  "CaseLimb", "CaseLabelList", "VariableList", "TryStatement",
  "CatchClause", "FinallyClause", "Expression", "ExpressionList",
  "SimpleExpression", "AdditionExpression", "Term", "Power", "Factor",
  "Variable", "TypeIdentifier", "Type", "SimpleType", "StructuredType",
  "ArrayBoundsList", "BoundType", "FieldList", "FixedPart",
  "RecordSection", "VariantPart", "VariantList", "VariantCaseList",
  "Variant", "VariantCaseLabelList", "Constant", "ConstantValue",
  "BasicConstant", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,    46,    40,    41,    59,    44,    61,    58,    91,
      93,    60,    62,    43,    45,    42,    47,    38,    64,    94
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    82,    82,    82,    82,    83,    83,    84,
      84,    85,    86,    87,    87,    88,    89,    90,    90,    91,
      91,    92,    93,    93,    94,    94,    95,    96,    96,    97,
      97,    98,    99,    99,   100,   100,   101,   102,   102,   103,
     103,   104,   104,   104,   104,   105,   105,   107,   106,   108,
     108,   109,   109,   110,   110,   111,   112,   113,   113,   113,
     114,   114,   114,   115,   115,   116,   116,   116,   116,   117,
     117,   118,   118,   119,   119,   120,   121,   121,   122,   122,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   124,   124,   125,   125,   126,   128,
     127,   129,   130,   129,   132,   133,   131,   135,   134,   137,
     136,   138,   139,   139,   140,   141,   141,   142,   143,   143,
     144,   144,   145,   146,   146,   147,   147,   148,   148,   148,
     148,   148,   148,   148,   148,   149,   149,   150,   150,   150,
     151,   151,   151,   151,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   153,   153,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   155,   155,   155,
     155,   156,   157,   157,   157,   158,   158,   158,   159,   159,
     159,   159,   160,   160,   161,   162,   162,   162,   162,   162,
     162,   162,   163,   163,   164,   164,   165,   165,   166,   167,
     167,   168,   169,   169,   170,   170,   170,   171,   171,   172,
     172,   172,   172
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     6,     3,     6,     3,     0,     3,     1,
       3,     1,     1,     1,     3,     2,     5,     0,     3,     1,
       3,     1,     0,     2,     1,     2,     4,     0,     2,     1,
       2,     4,     0,     2,     1,     2,     4,     0,     1,     2,
       3,     4,     3,     1,     3,     0,     1,     0,     4,     1,
       1,     1,     1,     1,     4,     3,     5,     0,     4,     5,
       0,     1,     1,     1,     3,     3,     4,     1,     1,     1,
       1,     7,     6,     1,     3,     5,     1,     3,     3,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     4,
       2,     1,     1,     1,     0,     3,     4,     3,     3,     0,
       5,     1,     0,     4,     0,     0,     6,     0,     6,     0,
       7,     1,     1,     1,     4,     1,     3,     3,     1,     3,
       1,     3,     6,     0,     6,     0,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     1,     3,     1,     2,     2,
       1,     3,     3,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     1,     1,     3,     2,     2,
       2,     2,     3,     4,     4,     4,     8,     1,     4,     3,
       2,     1,     1,     1,     2,     1,     3,     3,     6,     3,
       3,     2,     1,     3,     1,     0,     1,     2,     3,     4,
       1,     2,     1,     3,     3,     1,     6,     5,     1,     1,
       3,     5,     1,     3,     1,     2,     2,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     7,    12,     0,     0,     1,     0,
      17,     0,     6,     0,     4,     0,     9,     0,     0,    11,
       0,    22,    13,     0,     0,     8,     0,    21,     0,    19,
       2,     0,    43,    15,     0,    27,     0,     0,     0,    10,
      18,     0,     0,     0,     0,    93,     0,     0,     0,   107,
      91,     0,     0,   104,    46,   167,     0,     0,    45,    76,
      79,    83,    80,    84,    85,    86,    87,    88,    92,    94,
       0,    23,    24,     0,    32,     5,    14,     3,    20,    44,
       0,    45,   209,   211,   210,   212,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   137,   140,   144,
     153,   155,   156,     0,     0,    82,     0,   111,     0,    90,
      45,     0,   120,     0,     0,    42,    46,     0,     0,     0,
       0,     0,   170,    81,     0,    25,     0,    28,    29,     0,
      37,    97,     0,   159,     0,     0,     0,     0,   158,   135,
       0,   138,   139,   160,   161,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   112,     0,    99,
      45,   123,     0,     0,     0,    78,    77,    41,    98,   169,
       0,     0,     0,     0,   208,     0,   204,   207,     0,    30,
       0,    33,    34,     0,     0,    16,    38,     0,     0,    49,
      50,    96,     0,   171,     0,     0,   162,     0,   157,   114,
     115,     0,   118,   134,   129,   132,   133,   128,   130,   131,
     143,   141,   142,   149,   147,   148,   151,   152,   150,   145,
     146,   154,     0,     0,     0,     0,     0,   125,    89,   121,
     105,    95,   168,   205,   206,    26,     0,     0,   185,     0,
       0,     0,   171,   175,     0,   172,   173,     0,     0,    35,
      57,    57,     0,    39,    47,   165,   164,     0,   136,     0,
       0,     0,   163,   109,   101,   100,     0,     0,     0,     0,
       0,     0,   174,     0,     0,   195,     0,   186,   192,   190,
       0,     0,   181,    31,     0,     0,     0,     0,    55,    40,
      17,     0,   116,   119,   117,     0,   102,   108,     0,    45,
     122,   106,   184,     0,   182,     0,     0,     0,   179,   187,
     191,   180,   176,   177,    36,     0,     0,    67,    68,     0,
      63,     0,    53,     0,    51,    48,    52,     0,   110,     0,
       0,   126,     0,     0,     0,     0,   194,   193,   188,     0,
       0,    60,     0,    56,     0,     0,   103,    45,   183,     0,
       0,     0,   189,     0,     0,     0,    65,    70,    69,    61,
      62,    58,     0,    64,     0,   166,   124,   178,   197,   198,
     199,     0,   202,     0,    66,     0,     0,    59,    54,     0,
       0,     0,   196,     0,     0,    73,     0,   200,   203,   185,
       0,     0,     0,     0,     0,     0,    74,     0,     0,   201,
       0,    72,     0,    75,    71
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,    10,    15,    18,    55,   284,    19,    20,
      21,    28,    56,    35,    71,    72,    74,   127,   128,   130,
     191,   192,   195,   196,    33,    57,   197,   300,   285,   335,
     336,   199,   200,   297,   371,   329,   330,   366,   367,   394,
     395,    58,    59,    60,   123,    61,    62,    63,   234,   275,
     339,    64,   113,   280,    65,   108,    66,   305,   106,   168,
      67,   209,   210,   211,   111,    68,   237,   279,   139,   140,
      96,    97,    98,    99,   100,   101,   253,   254,   255,   256,
     313,   314,   286,   287,   288,   289,   378,   379,   380,   381,
     257,   186,   102
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -341
static const yytype_int16 yypact[] =
{
      56,    42,    42,    37,    36,  -341,    96,   138,  -341,    42,
      71,    42,  -341,    42,  -341,   114,  -341,   102,    50,  -341,
      84,   103,  -341,   134,   149,  -341,    42,  -341,   152,  -341,
    -341,   514,  -341,  -341,    42,    80,   101,    42,   120,  -341,
    -341,   102,   171,   546,   467,  -341,    42,   102,   467,  -341,
     467,   435,    42,  -341,  -341,  -341,    78,   180,   144,  -341,
    -341,  -341,  -341,  -341,  -341,  -341,  -341,  -341,  -341,   242,
     127,    42,  -341,    42,   176,  -341,  -341,  -341,  -341,  -341,
     216,   144,  -341,  -341,  -341,  -341,   221,   179,   191,   388,
     423,   221,   221,   221,   221,   205,    82,    62,   135,   235,
    -341,   257,  -341,    28,   177,  -341,   233,  -341,   435,  -341,
     144,    25,    45,   467,   556,  -341,   435,   274,   467,    42,
     467,   467,  -341,  -341,    46,  -341,   229,    42,  -341,    42,
      60,  -341,   280,  -341,    42,    42,   467,   244,  -341,  -341,
     -22,    62,    62,  -341,  -341,    46,   467,   467,   467,   467,
     467,   467,   467,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   467,  -341,  -341,   467,  -341,
     144,   301,   435,    42,   314,  -341,  -341,  -341,  -341,  -341,
     195,    77,   201,   201,  -341,   272,  -341,  -341,   373,  -341,
     146,    42,  -341,    42,    42,  -341,    60,   273,   277,  -341,
    -341,  -341,   253,  -341,   279,   299,  -341,   467,  -341,   281,
    -341,   175,  -341,  -341,  -341,  -341,  -341,  -341,  -341,  -341,
     135,   135,   135,   235,   235,   235,   235,   235,   235,   235,
     235,  -341,   196,   333,   435,   297,    42,   332,  -341,    45,
    -341,  -341,  -341,  -341,  -341,  -341,   284,    34,   147,   321,
      42,    42,   294,  -341,   291,  -341,  -341,   296,   373,  -341,
     298,   298,   295,  -341,  -341,  -341,  -341,   467,  -341,    46,
      46,   435,  -341,  -341,   347,  -341,   467,   312,   435,   348,
     435,    26,  -341,    12,   204,  -341,   349,   318,  -341,   320,
     373,   222,  -341,  -341,    46,   322,    65,   334,  -341,  -341,
      33,   370,  -341,  -341,  -341,   435,  -341,  -341,   373,   144,
    -341,  -341,  -341,   129,  -341,    42,   335,   373,  -341,   147,
    -341,  -341,  -341,  -341,  -341,    42,   219,  -341,  -341,    57,
    -341,    42,  -341,   338,  -341,  -341,  -341,   467,  -341,   435,
     435,  -341,    26,   331,   372,    42,  -341,  -341,   342,   259,
     148,    40,    17,  -341,   405,   351,  -341,   144,  -341,   373,
      46,   383,  -341,   148,   352,   409,  -341,  -341,  -341,  -341,
    -341,  -341,   354,  -341,   358,  -341,  -341,  -341,  -341,   359,
    -341,   263,  -341,    46,  -341,    42,   361,  -341,  -341,    46,
      46,   360,  -341,   364,    90,  -341,    42,  -341,  -341,   147,
      42,    42,   398,   363,   371,   366,  -341,   148,   404,  -341,
      42,  -341,    42,  -341,  -341
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -341,  -341,  -341,  -341,  -341,  -341,    -1,    -2,   140,  -341,
    -341,  -341,   128,  -341,  -341,   377,  -341,  -341,   315,  -341,
    -341,   252,  -341,  -341,  -341,   -54,   254,  -341,  -125,  -341,
    -341,  -268,  -262,   188,  -341,  -341,   106,  -340,  -341,  -341,
    -238,   -27,  -109,   350,  -341,  -341,   417,  -341,  -341,  -341,
    -341,  -341,  -341,  -341,  -341,  -341,  -341,  -341,  -111,  -341,
    -341,  -341,   199,  -341,  -341,  -341,  -341,  -341,   -31,   -55,
     356,   131,    19,   212,   -72,    -5,  -129,  -255,  -263,   227,
    -341,   136,    70,  -341,   158,   160,    97,  -341,    92,  -341,
       7,    81,   -50
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -209
static const yytype_int16 yytable[] =
{
       6,     7,   174,   295,   117,   198,   204,   176,    16,    23,
      22,    24,    22,    95,   133,     5,    81,   107,   312,   109,
       5,   143,   144,   384,   110,    39,    69,   132,   327,     5,
      82,    83,    84,    70,   328,   321,    76,     8,    69,   172,
     193,   104,   246,   166,   207,     5,    69,   112,   208,     5,
      82,    83,    84,   340,   194,   332,   171,    85,   137,   369,
      17,   333,   346,   238,     9,   180,   181,   411,     5,   325,
      70,   198,   126,   248,   187,   249,   167,    85,   372,   312,
     315,   170,   107,   193,   327,   370,     1,   178,   193,   250,
     328,   173,   231,    31,     2,   187,   153,   194,    17,   182,
     183,    32,   194,    69,   377,   205,    27,   119,   146,    69,
     232,    69,    30,   251,   121,    34,   235,   325,   179,   182,
     183,   351,   352,   184,   122,   274,   126,   190,    22,   202,
      73,   185,   187,   187,   203,   154,   155,   233,   187,   147,
     148,   149,   156,   207,   184,    29,   114,   242,   157,   150,
       5,     5,   212,   151,   152,   401,   364,   283,   403,    11,
     402,    12,   304,   406,   158,   307,    75,    69,   239,    78,
     193,   311,   220,   221,   222,   105,   268,   159,   160,    25,
      26,   184,   184,   365,   194,    77,   344,   252,    79,   190,
      22,   161,   260,   261,   124,   342,   338,   115,    36,   343,
      37,    13,   353,    14,     5,    82,    83,    84,   187,   116,
     162,   163,    37,    38,   258,    37,   361,    40,    41,   187,
     187,   368,   141,   142,     5,    82,    83,    84,   129,    69,
     356,   187,    85,   131,   368,   277,   301,   118,   145,   119,
     187,   270,   134,   271,   187,   107,   121,    22,   291,    22,
     292,   309,    85,    86,   135,   341,   122,   252,   187,   241,
     272,   207,   207,   243,   244,    87,    69,   187,   184,   184,
      37,   164,   317,    69,    88,    69,   212,   303,   368,   169,
     252,   413,   316,   414,    89,    37,   322,   350,    37,   252,
      90,   177,   187,   184,   326,    22,   188,   201,    93,    94,
      69,   323,   118,   376,   119,   120,   355,   252,   206,   187,
     187,   121,   236,   357,   203,   119,   252,   265,    22,   119,
     165,   122,   121,   349,    22,    37,   121,   363,   240,   390,
     203,   391,   122,   187,    69,    69,   122,   245,   263,   187,
     187,   252,   264,   266,   203,   267,   269,   273,   276,   203,
     326,    22,   278,   281,   290,  -208,   293,   294,   252,   184,
     299,   296,   203,   306,   359,   310,   318,   382,   223,   224,
     225,   226,   227,   228,   229,   230,     5,    82,    83,    84,
     308,   246,   184,   319,   393,   320,   337,   324,   184,   184,
     382,     5,    82,    83,    84,   393,   382,   398,    22,   405,
     393,   354,   331,   345,    85,   360,   203,   362,   247,   203,
     374,   203,   248,   136,   249,   375,   383,   386,   387,    85,
      86,   385,   388,   399,   389,   400,     5,    82,    83,    84,
     396,   407,    87,   408,   410,   409,   250,   412,     5,    27,
     334,    88,   189,   259,    43,    44,   182,   183,   125,   298,
     262,    89,   251,    45,    85,    86,    46,    90,   373,    47,
      48,    91,    92,   103,   175,    93,    94,    87,   302,   404,
       5,    82,    83,    84,   282,    49,    88,   347,   358,   348,
     392,   397,    50,     0,    51,     0,    89,     0,     0,    52,
      53,     0,    90,   138,     0,     0,    91,    92,    85,    86,
      93,    94,   213,   214,   215,   216,   217,   218,   219,     0,
       0,    87,     0,     0,     0,    42,     0,     5,    27,     0,
      88,     0,     0,    43,    44,     0,     0,     0,     0,     0,
      89,   -45,    45,     0,     0,    46,    90,     0,    47,    48,
      91,    92,     0,     0,    93,    94,     0,    80,     0,     5,
      27,     0,     0,     0,    49,    43,    44,     0,     0,     5,
       0,    50,     0,    51,    45,    43,    44,    46,    52,    53,
      47,    48,     0,     0,    45,     0,     0,    46,     0,    54,
      47,    48,     0,     0,     0,     0,    49,     0,     0,     0,
       0,     0,     0,    50,     0,    51,    49,     0,     0,     0,
      52,    53,     0,    50,     0,    51,     0,     0,     0,     0,
      52,    53
};

static const yytype_int16 yycheck[] =
{
       1,     2,   113,   258,    58,   130,   135,   116,     9,    11,
      11,    13,    13,    44,    86,     3,    43,    48,   281,    50,
       3,    93,    94,   363,    51,    26,    31,    81,   296,     3,
       4,     5,     6,    34,   296,   290,    37,     0,    43,    14,
      23,    46,     8,    15,    66,     3,    51,    52,    70,     3,
       4,     5,     6,   308,    37,    22,   110,    31,    89,    19,
      27,    28,   317,   172,    28,   120,   121,   407,     3,    52,
      71,   196,    73,    39,   124,    41,    48,    31,    61,   342,
      68,   108,   113,    23,   352,    45,    30,   118,    23,    63,
     352,    66,   164,     9,    38,   145,    34,    37,    27,    73,
      74,    17,    37,   108,   359,   136,     4,    62,    26,   114,
     165,   116,    62,    79,    69,    12,   170,    52,   119,    73,
      74,    64,    65,   124,    79,   234,   127,   129,   129,   134,
      50,   124,   182,   183,   135,    73,    74,   168,   188,    57,
      58,    59,     7,    66,   145,    17,    68,    70,    13,    67,
       3,     3,   145,    71,    72,    65,     8,    10,   396,    63,
      70,    65,   271,   401,    29,   276,    65,   172,   173,    41,
      23,   280,   153,   154,   155,    47,   207,    42,    43,    65,
      66,   182,   183,    35,    37,    65,   315,   188,    17,   191,
     191,    56,   193,   194,    67,    66,   305,    17,    64,    70,
      66,    63,   331,    65,     3,     4,     5,     6,   258,    65,
      75,    76,    66,    64,    68,    66,   345,    65,    66,   269,
     270,   350,    91,    92,     3,     4,     5,     6,    52,   234,
     339,   281,    31,    17,   363,   236,   267,    60,    33,    62,
     290,    66,    63,    68,   294,   276,    69,   248,   250,   250,
     251,   278,    31,    32,    63,   309,    79,   258,   308,    64,
      64,    66,    66,   182,   183,    44,   271,   317,   269,   270,
      66,    36,    68,   278,    53,   280,   269,   270,   407,    46,
     281,   410,   283,   412,    63,    66,    64,    68,    66,   290,
      69,    17,   342,   294,   296,   296,    67,    17,    77,    78,
     305,   294,    60,   357,    62,    63,   337,   308,    64,   359,
     360,    69,    11,   340,   315,    62,   317,    64,   319,    62,
      63,    79,    69,   325,   325,    66,    69,    68,    14,    66,
     331,    68,    79,   383,   339,   340,    79,    65,    65,   389,
     390,   342,    65,    64,   345,    46,    65,    14,    51,   350,
     352,   352,    20,    69,    33,    61,    65,    61,   359,   360,
      65,    63,   363,    16,    33,    17,    17,   360,   156,   157,
     158,   159,   160,   161,   162,   163,     3,     4,     5,     6,
      68,     8,   383,    65,   385,    65,    16,    65,   389,   390,
     383,     3,     4,     5,     6,   396,   389,   390,   399,   400,
     401,    63,    68,    68,    31,    33,   407,    65,    35,   410,
       5,   412,    39,    25,    41,    64,    33,     8,    64,    31,
      32,    69,    64,    63,    65,    61,     3,     4,     5,     6,
      69,    33,    44,    70,    68,    64,    63,    33,     3,     4,
     300,    53,   127,   191,     9,    10,    73,    74,    71,   261,
     196,    63,    79,    18,    31,    32,    21,    69,   352,    24,
      25,    73,    74,    46,   114,    77,    78,    44,   269,   399,
       3,     4,     5,     6,   247,    40,    53,   319,   342,   319,
     383,   389,    47,    -1,    49,    -1,    63,    -1,    -1,    54,
      55,    -1,    69,    70,    -1,    -1,    73,    74,    31,    32,
      77,    78,   146,   147,   148,   149,   150,   151,   152,    -1,
      -1,    44,    -1,    -1,    -1,     1,    -1,     3,     4,    -1,
      53,    -1,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,
      63,    17,    18,    -1,    -1,    21,    69,    -1,    24,    25,
      73,    74,    -1,    -1,    77,    78,    -1,     1,    -1,     3,
       4,    -1,    -1,    -1,    40,     9,    10,    -1,    -1,     3,
      -1,    47,    -1,    49,    18,     9,    10,    21,    54,    55,
      24,    25,    -1,    -1,    18,    -1,    -1,    21,    -1,    65,
      24,    25,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    49,    40,    -1,    -1,    -1,
      54,    55,    -1,    47,    -1,    49,    -1,    -1,    -1,    -1,
      54,    55
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    38,    81,    82,     3,    86,    86,     0,    28,
      83,    63,    65,    63,    65,    84,    86,    27,    85,    88,
      89,    90,    86,    87,    87,    65,    66,     4,    91,    92,
      62,     9,    17,   104,    12,    93,    64,    66,    64,    86,
      65,    66,     1,     9,    10,    18,    21,    24,    25,    40,
      47,    49,    54,    55,    65,    86,    92,   105,   121,   122,
     123,   125,   126,   127,   131,   134,   136,   140,   145,   155,
      86,    94,    95,    50,    96,    65,    86,    65,    92,    17,
       1,   121,     4,     5,     6,    31,    32,    44,    53,    63,
      69,    73,    74,    77,    78,   148,   150,   151,   152,   153,
     154,   155,   172,   126,   155,    92,   138,   148,   135,   148,
     121,   144,   155,   132,    68,    17,    65,   105,    60,    62,
      63,    69,    79,   124,    67,    95,    86,    97,    98,    52,
      99,    17,   105,   154,    63,    63,    25,   148,    70,   148,
     149,   151,   151,   154,   154,    33,    26,    57,    58,    59,
      67,    71,    72,    34,    73,    74,     7,    13,    29,    42,
      43,    56,    75,    76,    36,    63,    15,    48,   139,    46,
     121,   105,    14,    66,   138,   123,   122,    17,   148,    86,
     149,   149,    73,    74,    86,   170,   171,   172,    67,    98,
      87,   100,   101,    23,    37,   102,   103,   106,   108,   111,
     112,    17,   155,    86,   156,   148,    64,    66,    70,   141,
     142,   143,   170,   150,   150,   150,   150,   150,   150,   150,
     152,   152,   152,   153,   153,   153,   153,   153,   153,   153,
     153,   154,   149,   148,   128,   105,    11,   146,   122,   155,
      14,    64,    70,   171,   171,    65,     8,    35,    39,    41,
      63,    79,    86,   156,   157,   158,   159,   170,    68,   101,
      86,    86,   106,    65,    65,    64,    64,    46,   148,    65,
      66,    68,    64,    14,   122,   129,    51,    86,    20,   147,
     133,    69,   159,    10,    87,   108,   162,   163,   164,   165,
      33,    87,    86,    65,    61,   157,    63,   113,   113,    65,
     107,   148,   142,   170,   122,   137,    16,   138,    68,   121,
      17,   122,   158,   160,   161,    68,    86,    68,    17,    65,
      65,   157,    64,   170,    65,    52,    87,   111,   112,   115,
     116,    68,    22,    28,    88,   109,   110,    16,   122,   130,
     157,   105,    66,    70,   156,    68,   157,   164,   165,    87,
      68,    64,    65,   156,    63,   148,   122,   121,   161,    33,
      33,   156,    65,    68,     8,    35,   117,   118,   156,    19,
      45,   114,    61,   116,     5,    64,   105,   157,   166,   167,
     168,   169,   170,    33,   117,    69,     8,    64,    64,    65,
      66,    68,   166,    86,   119,   120,    69,   168,   170,    63,
      61,    65,    70,   120,   162,    86,   120,    33,    70,    64,
      68,   117,    33,   156,   156
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
        case 3:
#line 964 "dpas-parser.y"
    {
				jit_free((yyvsp[(2) - (6)].name));
				identifier_list_free((yyvsp[(4) - (6)].id_list).list, (yyvsp[(4) - (6)].id_list).len);
			}
    break;

  case 4:
#line 968 "dpas-parser.y"
    {
				jit_free((yyvsp[(2) - (3)].name));
			}
    break;

  case 5:
#line 971 "dpas-parser.y"
    {
				/* The "module" keyword is provided as an alternative
				   to "program" because it looks odd to put "program"
				   on code included via an "import" clause */
				jit_free((yyvsp[(2) - (6)].name));
				identifier_list_free((yyvsp[(4) - (6)].id_list).list, (yyvsp[(4) - (6)].id_list).len);
			}
    break;

  case 6:
#line 978 "dpas-parser.y"
    {
				jit_free((yyvsp[(2) - (3)].name));
			}
    break;

  case 9:
#line 989 "dpas-parser.y"
    {
				dpas_import((yyvsp[(1) - (1)].name));
				jit_free((yyvsp[(1) - (1)].name));
			}
    break;

  case 10:
#line 993 "dpas-parser.y"
    {
				dpas_import((yyvsp[(3) - (3)].name));
				jit_free((yyvsp[(3) - (3)].name));
			}
    break;

  case 11:
#line 1000 "dpas-parser.y"
    {
				/* Get the "main" function for this module */
				jit_function_t func = dpas_current_function();

				/* Make sure that the function is properly terminated */
				if(!jit_insn_default_return(func))
				{
					dpas_out_of_memory();
				}

				/* Dump the before-compile state of the function */
				if(dpas_dump_functions)
				{
					jit_dump_function(stdout, func, "main");
				}

				/* Compile the procedure/function */
				if(!jit_function_compile(func))
				{
					dpas_out_of_memory();
				}

				/* Dump the after-compile state of the function */
				if(dpas_dump_functions > 1)
				{
					jit_dump_function(stdout, func, "main");
				}

				/* Add the function to the "main" list, for later execution */
				dpas_add_main_function(func);

				/* Pop the "main" function */
				dpas_pop_function();
			}
    break;

  case 12:
#line 1041 "dpas-parser.y"
    { (yyval.name) = (yyvsp[(1) - (1)].name); }
    break;

  case 13:
#line 1045 "dpas-parser.y"
    {
				(yyval.id_list).list = 0;
				(yyval.id_list).len = 0;
				identifier_list_add(&((yyval.id_list).list), &((yyval.id_list).len), (yyvsp[(1) - (1)].name));
			}
    break;

  case 14:
#line 1050 "dpas-parser.y"
    {
				(yyval.id_list) = (yyvsp[(1) - (3)].id_list);
				if(identifier_list_contains((yyval.id_list).list, (yyval.id_list).len, (yyvsp[(3) - (3)].name)))
				{
					dpas_error("`%s' declared twice in an identifier list", (yyvsp[(3) - (3)].name));
					identifier_list_add(&((yyval.id_list).list), &((yyval.id_list).len), 0);
					jit_free((yyvsp[(3) - (3)].name));
				}
				else
				{
					identifier_list_add(&((yyval.id_list).list), &((yyval.id_list).len), (yyvsp[(3) - (3)].name));
				}
			}
    break;

  case 21:
#line 1089 "dpas-parser.y"
    { /* label declarations are ignored */ }
    break;

  case 26:
#line 1103 "dpas-parser.y"
    {
				dpas_scope_item_t item;
				item = dpas_scope_lookup(dpas_scope_current(), (yyvsp[(1) - (4)].name), 0);
				if(item)
				{
					dpas_redeclared((yyvsp[(1) - (4)].name), item);
				}
				else
				{
					dpas_scope_add_const(dpas_scope_current(), (yyvsp[(1) - (4)].name), &((yyvsp[(3) - (4)].const_value)),
										 dpas_filename, dpas_linenum);
				}
				jit_free((yyvsp[(1) - (4)].name));
				jit_type_free((yyvsp[(3) - (4)].const_value).type);
			}
    break;

  case 28:
#line 1122 "dpas-parser.y"
    {
				/* Check for undefined record types that were referred
				   to using a pointer reference of the form "^name" */
				dpas_scope_check_undefined(dpas_scope_current());
			}
    break;

  case 31:
#line 1135 "dpas-parser.y"
    {
				dpas_scope_item_t item;
				jit_type_t type;
				item = dpas_scope_lookup(dpas_scope_current(), (yyvsp[(1) - (4)].name), 0);
				type = (item ? dpas_scope_item_type(item) : 0);
				if(!item)
				{
					dpas_type_set_name((yyvsp[(3) - (4)].type), (yyvsp[(1) - (4)].name));
					dpas_scope_add(dpas_scope_current(), (yyvsp[(1) - (4)].name), (yyvsp[(3) - (4)].type),
								   DPAS_ITEM_TYPE, 0, 0,
								   dpas_filename, dpas_linenum);
				}
				else if(dpas_scope_item_kind(item) == DPAS_ITEM_TYPE &&
					    jit_type_get_tagged_kind(type) == DPAS_TAG_NAME &&
					    jit_type_get_tagged_type(type) == 0 &&
						jit_type_get_tagged_kind((yyvsp[(3) - (4)].type)) == DPAS_TAG_NAME)
				{
					/* This is a defintion of a record type that was
					   previously encountered in a forward pointer
					   reference of the form "^name".  We need to
					   back-patch the previous type with the type info */
					jit_type_set_tagged_type
						(type, jit_type_get_tagged_type((yyvsp[(3) - (4)].type)), 1);
				}
				else
				{
					dpas_redeclared((yyvsp[(1) - (4)].name), item);
				}
				jit_free((yyvsp[(1) - (4)].name));
				jit_type_free((yyvsp[(3) - (4)].type));
			}
    break;

  case 36:
#line 1179 "dpas-parser.y"
    {
				/* Add each of the variables to the current scope */
				int posn;
				dpas_scope_item_t item;
				for(posn = 0; posn < (yyvsp[(1) - (4)].id_list).len; ++posn)
				{
					item = dpas_scope_lookup(dpas_scope_current(),
										     (yyvsp[(1) - (4)].id_list).list[posn], 0);
					if(item)
					{
						dpas_redeclared((yyvsp[(1) - (4)].id_list).list[posn], item);
					}
					else
					{
						if(!dpas_scope_is_module())
						{
							jit_value_t value;
							value = jit_value_create
								(dpas_current_function(), (yyvsp[(3) - (4)].type));
							if(!value)
							{
								dpas_out_of_memory();
							}
							dpas_scope_add(dpas_scope_current(),
										   (yyvsp[(1) - (4)].id_list).list[posn], (yyvsp[(3) - (4)].type),
										   DPAS_ITEM_VARIABLE, value, 0,
										   dpas_filename, dpas_linenum);
						}
						else
						{
							/* Allocate some memory to hold the global data */
							void *space = jit_calloc(1, jit_type_get_size((yyvsp[(3) - (4)].type)));
							if(!space)
							{
								dpas_out_of_memory();
							}
							dpas_scope_add(dpas_scope_current(),
										   (yyvsp[(1) - (4)].id_list).list[posn], (yyvsp[(3) - (4)].type),
										   DPAS_ITEM_GLOBAL_VARIABLE, space, 0,
										   dpas_filename, dpas_linenum);
						}
					}
				}

				/* Free the id list and type, which we don't need any more */
				identifier_list_free((yyvsp[(1) - (4)].id_list).list, (yyvsp[(1) - (4)].id_list).len);
				jit_type_free((yyvsp[(3) - (4)].type));
			}
    break;

  case 47:
#line 1256 "dpas-parser.y"
    {
				unsigned int num_params;
				unsigned int param;
				jit_type_t type;
				const char *name;
				dpas_scope_item_t item;
				jit_function_t func;

				/* Declare the procedure/function into the current scope */
				item = dpas_scope_lookup(dpas_scope_current(), (yyvsp[(1) - (2)].procedure).name, 0);
				if(item)
				{
					dpas_redeclared((yyvsp[(1) - (2)].procedure).name, item);
					item = 0;
				}
				else
				{
					dpas_scope_add(dpas_scope_current(), (yyvsp[(1) - (2)].procedure).name, (yyvsp[(1) - (2)].procedure).type,
								   DPAS_ITEM_PROCEDURE, 0, 0,
								   dpas_filename, dpas_linenum);
					item = dpas_scope_lookup(dpas_scope_current(), (yyvsp[(1) - (2)].procedure).name, 0);
				}

				/* Push into a new scope for the procedure/function body */
				dpas_scope_push();
				func = dpas_new_function((yyvsp[(1) - (2)].procedure).type);
				if(item)
				{
					dpas_scope_item_set_info(item, func);
				}

				/* Declare the parameters into the scope.  If a name
				   is NULL, then it indicates that a duplicate parameter
				   name was detected, and replaced with no name */
				num_params = jit_type_num_params((yyvsp[(1) - (2)].procedure).type);
				for(param = 0; param < num_params; ++param)
				{
					name = jit_type_get_name((yyvsp[(1) - (2)].procedure).type, param);
					if(name)
					{
						jit_value_t value;
						value = jit_value_get_param(func, param);
						if(!value)
						{
							dpas_out_of_memory();
						}
						dpas_scope_add(dpas_scope_current(), name,
									   jit_type_get_param((yyvsp[(1) - (2)].procedure).type, param),
									   DPAS_ITEM_VARIABLE, value, 0,
									   dpas_filename, dpas_linenum);
					}
				}

				/* Declare the function return variable into the scope */
				type = jit_type_get_return((yyvsp[(1) - (2)].procedure).type);
				if(type != jit_type_void)
				{
					if(dpas_scope_lookup(dpas_scope_current(), (yyvsp[(1) - (2)].procedure).name, 0))
					{
						dpas_error("`%s' is declared as both a parameter "
								   "and a function name", (yyvsp[(1) - (2)].procedure).name);
					}
				}
			}
    break;

  case 48:
#line 1319 "dpas-parser.y"
    {
				jit_function_t func = dpas_current_function();
				int result;

				/* Make sure that the function is properly terminated */
				result = jit_insn_default_return(func);
				if(!result)
				{
					dpas_out_of_memory();
				}
				else if(result == 1 &&
				        jit_type_get_return((yyvsp[(1) - (4)].procedure).type) != jit_type_void)
				{
					dpas_error("control reached the end of a function");
				}

				/* Pop from the procedure/function scope */
				dpas_pop_function();
				dpas_scope_pop();

				/* Dump the before-compile state of the function */
				if(dpas_dump_functions)
				{
					jit_dump_function(stdout, func, (yyvsp[(1) - (4)].procedure).name);
				}

				/* Compile the procedure/function */
				if(!jit_function_compile(func))
				{
					dpas_out_of_memory();
				}

				/* Dump the after-compile state of the function */
				if(dpas_dump_functions > 1)
				{
					jit_dump_function(stdout, func, (yyvsp[(1) - (4)].procedure).name);
				}

				/* Free values that we no longer require */
				jit_free((yyvsp[(1) - (4)].procedure).name);
				jit_type_free((yyvsp[(1) - (4)].procedure).type);
			}
    break;

  case 49:
#line 1364 "dpas-parser.y"
    { (yyval.procedure) = (yyvsp[(1) - (1)].procedure); }
    break;

  case 50:
#line 1365 "dpas-parser.y"
    { (yyval.procedure) = (yyvsp[(1) - (1)].procedure); }
    break;

  case 51:
#line 1369 "dpas-parser.y"
    {}
    break;

  case 52:
#line 1370 "dpas-parser.y"
    {}
    break;

  case 53:
#line 1374 "dpas-parser.y"
    { (yyval.name) = 0; }
    break;

  case 54:
#line 1375 "dpas-parser.y"
    { (yyval.name) = (yyvsp[(3) - (4)].name); }
    break;

  case 55:
#line 1379 "dpas-parser.y"
    {
				(yyval.procedure).name = (yyvsp[(2) - (3)].name);
				(yyval.procedure).type = jit_type_create_signature
					((yyvsp[(3) - (3)].parameters).abi, jit_type_void,
					 (yyvsp[(3) - (3)].parameters).types, (unsigned int)((yyvsp[(3) - (3)].parameters).len), 1);
				if(!((yyval.procedure).type))
				{
					dpas_out_of_memory();
				}
				if(!jit_type_set_names((yyval.procedure).type, (yyvsp[(3) - (3)].parameters).names,
									   (unsigned int)((yyvsp[(3) - (3)].parameters).len)))
				{
					dpas_out_of_memory();
				}
				parameter_list_free(&((yyvsp[(3) - (3)].parameters)));
			}
    break;

  case 56:
#line 1398 "dpas-parser.y"
    {
				(yyval.procedure).name = (yyvsp[(2) - (5)].name);
				(yyval.procedure).type = jit_type_create_signature
					((yyvsp[(3) - (5)].parameters).abi, (yyvsp[(5) - (5)].type), (yyvsp[(3) - (5)].parameters).types, (unsigned int)((yyvsp[(3) - (5)].parameters).len), 1);
				if(!((yyval.procedure).type))
				{
					dpas_out_of_memory();
				}
				if(!jit_type_set_names((yyval.procedure).type, (yyvsp[(3) - (5)].parameters).names,
									   (unsigned int)((yyvsp[(3) - (5)].parameters).len)))
				{
					dpas_out_of_memory();
				}
				parameter_list_free(&((yyvsp[(3) - (5)].parameters)));
				jit_type_free((yyvsp[(5) - (5)].type));
			}
    break;

  case 57:
#line 1417 "dpas-parser.y"
    { parameter_list_init(&((yyval.parameters))); }
    break;

  case 58:
#line 1418 "dpas-parser.y"
    {
				(yyval.parameters) = (yyvsp[(2) - (4)].parameters);
				(yyval.parameters).abi = (yyvsp[(4) - (4)].abi);
			}
    break;

  case 59:
#line 1422 "dpas-parser.y"
    {
				(yyval.parameters) = (yyvsp[(2) - (5)].parameters);
				(yyval.parameters).abi = jit_abi_vararg;
			}
    break;

  case 60:
#line 1429 "dpas-parser.y"
    { (yyval.abi) = jit_abi_cdecl; }
    break;

  case 61:
#line 1430 "dpas-parser.y"
    { (yyval.abi) = jit_abi_fastcall; }
    break;

  case 62:
#line 1431 "dpas-parser.y"
    { (yyval.abi) = jit_abi_stdcall; }
    break;

  case 63:
#line 1435 "dpas-parser.y"
    { (yyval.parameters) = (yyvsp[(1) - (1)].parameters); }
    break;

  case 64:
#line 1436 "dpas-parser.y"
    {
				(yyval.parameters) = (yyvsp[(1) - (3)].parameters);
				parameter_list_merge(&((yyval.parameters)), &((yyvsp[(3) - (3)].parameters)));
			}
    break;

  case 65:
#line 1443 "dpas-parser.y"
    {
				parameter_list_create(&((yyval.parameters)), (yyvsp[(1) - (3)].id_list).list, (yyvsp[(1) - (3)].id_list).len, (yyvsp[(3) - (3)].param_type).type);
				if((yyvsp[(3) - (3)].param_type).bounds.len > 0)
				{
					/* We should be using "var" with conformant array types */
					dpas_warning("`%s' should be declared as `var'",
								 (yyvsp[(1) - (3)].id_list).list[0]);
					if((yyvsp[(1) - (3)].id_list).len > 1)
					{
						dpas_error("too many parameter names for "
								   "conformant array specification");
					}
					parameter_list_merge(&((yyval.parameters)), &((yyvsp[(3) - (3)].param_type).bounds));
				}
				jit_type_free((yyvsp[(3) - (3)].param_type).type);
			}
    break;

  case 66:
#line 1459 "dpas-parser.y"
    {
				jit_type_t type = jit_type_create_pointer((yyvsp[(4) - (4)].param_type).type, 0);
				if(!type)
				{
					dpas_out_of_memory();
				}
				if((yyvsp[(4) - (4)].param_type).bounds.len == 0)
				{
					type = jit_type_create_tagged(type, DPAS_TAG_VAR, 0, 0, 0);
					if(!type)
					{
						dpas_out_of_memory();
					}
				}
				parameter_list_create(&((yyval.parameters)), (yyvsp[(2) - (4)].id_list).list, (yyvsp[(2) - (4)].id_list).len, type);
				if((yyvsp[(4) - (4)].param_type).bounds.len > 0)
				{
					if((yyvsp[(2) - (4)].id_list).len > 1)
					{
						dpas_error("too many parameter names for "
								   "conformant array specification");
					}
					parameter_list_merge(&((yyval.parameters)), &((yyvsp[(4) - (4)].param_type).bounds));
				}
				jit_type_free(type);
			}
    break;

  case 67:
#line 1485 "dpas-parser.y"
    {
				parameter_list_init(&((yyval.parameters)));
				parameter_list_add(&((yyval.parameters)), (yyvsp[(1) - (1)].procedure).name, (yyvsp[(1) - (1)].procedure).type);
			}
    break;

  case 68:
#line 1489 "dpas-parser.y"
    {
				parameter_list_init(&((yyval.parameters)));
				parameter_list_add(&((yyval.parameters)), (yyvsp[(1) - (1)].procedure).name, (yyvsp[(1) - (1)].procedure).type);
			}
    break;

  case 69:
#line 1496 "dpas-parser.y"
    {
				(yyval.param_type).type = (yyvsp[(1) - (1)].type);
				parameter_list_init(&((yyval.param_type).bounds));
			}
    break;

  case 70:
#line 1500 "dpas-parser.y"
    { (yyval.param_type) = (yyvsp[(1) - (1)].param_type); }
    break;

  case 71:
#line 1504 "dpas-parser.y"
    {
				(yyval.param_type).type = dpas_create_conformant_array((yyvsp[(7) - (7)].type), (yyvsp[(4) - (7)].parameters).len, 1);
				(yyval.param_type).bounds = (yyvsp[(4) - (7)].parameters);
			}
    break;

  case 72:
#line 1508 "dpas-parser.y"
    {
				(yyval.param_type).type = dpas_create_conformant_array((yyvsp[(6) - (6)].param_type).type, (yyvsp[(3) - (6)].parameters).len, 0);
				(yyval.param_type).bounds = (yyvsp[(3) - (6)].parameters);
				parameter_list_merge(&((yyval.param_type).bounds), &((yyvsp[(6) - (6)].param_type).bounds));
			}
    break;

  case 73:
#line 1516 "dpas-parser.y"
    { (yyval.parameters) = (yyvsp[(1) - (1)].parameters); }
    break;

  case 74:
#line 1517 "dpas-parser.y"
    {
				(yyval.parameters) = (yyvsp[(1) - (3)].parameters);
				parameter_list_merge(&((yyval.parameters)), &((yyvsp[(3) - (3)].parameters)));
			}
    break;

  case 75:
#line 1524 "dpas-parser.y"
    {
				if((yyvsp[(5) - (5)].type) != jit_type_int)
				{
					char *name = dpas_type_name((yyvsp[(5) - (5)].type));
					dpas_error("`%s' cannot be used for array bounds; "
							   "must be `Integer'", name);
					jit_free(name);
				}
				jit_type_free((yyvsp[(5) - (5)].type));
				parameter_list_init(&((yyval.parameters)));
				parameter_list_add(&((yyval.parameters)), (yyvsp[(1) - (5)].name), jit_type_int);
				if(jit_strcmp((yyvsp[(1) - (5)].name), (yyvsp[(3) - (5)].name)) != 0)
				{
					parameter_list_add(&((yyval.parameters)), (yyvsp[(3) - (5)].name), jit_type_int);
				}
				else
				{
					dpas_error("`%s' used twice in a parameter or "
							   "field list", (yyvsp[(1) - (5)].name));
					parameter_list_add(&((yyval.parameters)), 0, jit_type_int);
					jit_free((yyvsp[(3) - (5)].name));
				}
			}
    break;

  case 80:
#line 1564 "dpas-parser.y"
    { /* Nothing to do here */ }
    break;

  case 81:
#line 1565 "dpas-parser.y"
    {
				/* Call a procedure or an ignored-result function */
				if(dpas_sem_is_builtin((yyvsp[(1) - (2)].semvalue)))
				{
					/* Expand a call to a builtin procedure */
					dpas_expand_builtin
						(dpas_sem_get_builtin((yyvsp[(1) - (2)].semvalue)), (yyvsp[(2) - (2)].expr_list).exprs, (yyvsp[(2) - (2)].expr_list).len);
				}
				else if(dpas_sem_is_procedure((yyvsp[(1) - (2)].semvalue)))
				{
					/* Invoke a user-defined procedure */
					dpas_scope_item_t item = dpas_sem_get_procedure((yyvsp[(1) - (2)].semvalue));
					invoke_procedure
						((jit_function_t)dpas_scope_item_info(item),
						 dpas_scope_item_name(item),
						 dpas_scope_item_type(item), 0, (yyvsp[(2) - (2)].expr_list).exprs, (yyvsp[(2) - (2)].expr_list).len);
				}
				else if(dpas_sem_is_rvalue((yyvsp[(1) - (2)].semvalue)) &&
						jit_type_is_signature(dpas_sem_get_type((yyvsp[(1) - (2)].semvalue))))
				{
					/* Invoke a procedure via an indirect pointer */
					invoke_procedure
						(0, 0, dpas_sem_get_type((yyvsp[(1) - (2)].semvalue)), dpas_sem_get_value((yyvsp[(1) - (2)].semvalue)),
						 (yyvsp[(2) - (2)].expr_list).exprs, (yyvsp[(2) - (2)].expr_list).len);
				}
				else
				{
					if(!dpas_sem_is_error((yyvsp[(1) - (2)].semvalue)))
					{
						dpas_error("invalid function or procedure name");
					}
				}
				expression_list_free((yyvsp[(2) - (2)].expr_list).exprs, (yyvsp[(2) - (2)].expr_list).len);
			}
    break;

  case 82:
#line 1599 "dpas-parser.y"
    {
				/* TODO */
				dpas_error("`goto' statements not yet implemented");
			}
    break;

  case 89:
#line 1609 "dpas-parser.y"
    {
				/* TODO */
				dpas_error("`with' statements not yet implemented");
			}
    break;

  case 90:
#line 1613 "dpas-parser.y"
    {
				/* TODO */
				dpas_error("`throw' statements not yet implemented");
			}
    break;

  case 91:
#line 1617 "dpas-parser.y"
    {
				/* TODO */
				dpas_error("`throw' statements not yet implemented");
			}
    break;

  case 93:
#line 1622 "dpas-parser.y"
    {
				/* Exit from the current loop level */
				if(loop_stack_size > 0)
				{
					if(!jit_insn_branch
						(dpas_current_function(),
						 &(loop_stack[loop_stack_size - 1].exit_label)))
					{
						dpas_out_of_memory();
					}
				}
				else
				{
					dpas_error("`exit' used outside loop");
				}
			}
    break;

  case 94:
#line 1641 "dpas-parser.y"
    { (yyval.expr_list).exprs = 0; (yyval.expr_list).len = 0; }
    break;

  case 95:
#line 1642 "dpas-parser.y"
    { (yyval.expr_list) = (yyvsp[(2) - (3)].expr_list); }
    break;

  case 98:
#line 1651 "dpas-parser.y"
    {
				jit_type_t ltype;
				jit_type_t rtype;
				jit_value_t dest;
				jit_value_t value;

				/* Convert variable references to the current function
				   into function return semantic values */
				if(dpas_sem_is_procedure((yyvsp[(1) - (3)].semvalue)) &&
				   ((jit_function_t)dpas_scope_item_info
				   			(dpas_sem_get_procedure((yyvsp[(1) - (3)].semvalue)))) ==
						dpas_current_function())
				{
					dpas_sem_set_return
						((yyvsp[(1) - (3)].semvalue), jit_type_get_return(dpas_sem_get_type((yyvsp[(1) - (3)].semvalue))));
				}

				/* Validate the l-value expression */
				if(!dpas_sem_is_lvalue((yyvsp[(1) - (3)].semvalue)) && !dpas_sem_is_lvalue_ea((yyvsp[(1) - (3)].semvalue)) &&
				   !dpas_sem_is_return((yyvsp[(1) - (3)].semvalue)))
				{
					if(!dpas_sem_is_error((yyvsp[(1) - (3)].semvalue)))
					{
						dpas_error("invalid l-value in assignment statement");
					}
					ltype = jit_type_void;
				}
				else
				{
					ltype = dpas_sem_get_type((yyvsp[(1) - (3)].semvalue));
				}

				/* Validate the r-value expression */
				if(!dpas_sem_is_rvalue((yyvsp[(3) - (3)].semvalue)))
				{
					if(!dpas_sem_is_error((yyvsp[(3) - (3)].semvalue)))
					{
						dpas_error("invalid r-value in assignment statement");
					}
					rtype = jit_type_void;
				}
				else
				{
					rtype = dpas_sem_get_type((yyvsp[(3) - (3)].semvalue));
				}

				/* Type-check the source against the destination */
				/* TODO */
				value = dpas_sem_get_value((yyvsp[(3) - (3)].semvalue));

				/* Determine the kind of assignment we should perform */
				if(dpas_sem_is_return((yyvsp[(1) - (3)].semvalue)) && rtype != jit_type_void)
				{
					/* We are returning a value from this function */
					if(dpas_sem_is_lvalue_ea((yyvsp[(3) - (3)].semvalue)))
					{
						if(!jit_insn_return_ptr
								(dpas_current_function(), value, ltype))
						{
							dpas_out_of_memory();
						}
					}
					else
					{
						if(!jit_insn_return
								(dpas_current_function(), value))
						{
							dpas_out_of_memory();
						}
					}
				}
				else if(dpas_sem_is_lvalue_ea((yyvsp[(1) - (3)].semvalue)) && rtype != jit_type_void)
				{
					/* The destination is specified as an effective address */
					dest = dpas_sem_get_value((yyvsp[(1) - (3)].semvalue));
					if(dpas_type_is_record(ltype))
					{
						/* We need an effective address for the source */
						if(!dpas_sem_is_lvalue_ea((yyvsp[(3) - (3)].semvalue)))
						{
							value = jit_insn_address_of
								(dpas_current_function(), value);
							if(!value)
							{
								dpas_out_of_memory();
							}
						}
						if(!jit_insn_memcpy
							(dpas_current_function(), dest, value,
							 jit_value_create_nint_constant
							 	(dpas_current_function(), jit_type_nint,
								 (jit_nint)jit_type_get_size(rtype))))
						{
							dpas_out_of_memory();
						}
					}
					else
					{
						/* Don't use an effective address for the source */
						if(dpas_sem_is_lvalue_ea((yyvsp[(3) - (3)].semvalue)))
						{
							value = jit_insn_load_relative
								(dpas_current_function(), value, 0, rtype);
							if(!value)
							{
								dpas_out_of_memory();
							}
						}
						if(!jit_insn_store_relative
							(dpas_current_function(), dest, 0, value))
						{
							dpas_out_of_memory();
						}
					}
				}
				else if(dpas_sem_is_lvalue((yyvsp[(1) - (3)].semvalue)) && rtype != jit_type_void)
				{
					/* The destination is specified as a local value */
					dest = dpas_sem_get_value((yyvsp[(1) - (3)].semvalue));
					if(dpas_type_is_record(ltype))
					{
						/* We need effective addresses for both */
						if(!dpas_sem_is_lvalue_ea((yyvsp[(1) - (3)].semvalue)))
						{
							dest = jit_insn_address_of
								(dpas_current_function(), dest);
							if(!dest)
							{
								dpas_out_of_memory();
							}
						}
						if(!dpas_sem_is_lvalue_ea((yyvsp[(3) - (3)].semvalue)))
						{
							value = jit_insn_address_of
								(dpas_current_function(), value);
							if(!value)
							{
								dpas_out_of_memory();
							}
						}
						if(!jit_insn_memcpy
							(dpas_current_function(), dest, value,
							 jit_value_create_nint_constant
							 	(dpas_current_function(), jit_type_nint,
								 (jit_nint)jit_type_get_size(rtype))))
						{
							dpas_out_of_memory();
						}
					}
					else
					{
						/* Don't use an effective address for the source */
						if(dpas_sem_is_lvalue_ea((yyvsp[(3) - (3)].semvalue)))
						{
							value = jit_insn_load_relative
								(dpas_current_function(), value, 0, rtype);
							if(!value)
							{
								dpas_out_of_memory();
							}
						}
						if(!jit_insn_store
							(dpas_current_function(), dest, value))
						{
							dpas_out_of_memory();
						}
					}
				}

				/* Return the l-value for use by "for" statements */
				(yyval.semvalue) = (yyvsp[(1) - (3)].semvalue);
			}
    break;

  case 99:
#line 1826 "dpas-parser.y"
    {
				jit_label_t label = jit_label_undefined;

				/* Check the condition and jump if false */
				if(!jit_insn_branch_if_not
						(dpas_current_function(),
						 dpas_sem_get_value((yyvsp[(2) - (3)].semvalue)), &label))
				{
					dpas_out_of_memory();
				}

				/* Push into an "if" context, to remember the label */
				push_if(label);

			}
    break;

  case 100:
#line 1840 "dpas-parser.y"
    {

				/* Set the final label at the end of the "if" */
				if(if_stack[if_stack_size - 1] != jit_label_undefined)
				{
					if(!jit_insn_label
							(dpas_current_function(),
							 &(if_stack[if_stack_size - 1])))
					{
						dpas_out_of_memory();
					}
				}
				--if_stack_size;
			}
    break;

  case 102:
#line 1858 "dpas-parser.y"
    {
				jit_label_t label = jit_label_undefined;

				/* Jump to the end of the "if" statement */
				if(!jit_block_current_is_dead(dpas_current_function()))
				{
					if(!jit_insn_branch(dpas_current_function(), &label))
					{
						dpas_out_of_memory();
					}
				}

				/* Set the position of the "else" clause */
				if(!jit_insn_label
						(dpas_current_function(),
						 &(if_stack[if_stack_size - 1])))
				{
					dpas_out_of_memory();
				}

				/* Replace the end point of the "if" */
				if_stack[if_stack_size - 1] = label;

			}
    break;

  case 104:
#line 1885 "dpas-parser.y"
    {
				jit_label_t label = jit_label_undefined;

				/* Jump to the beginning of the expression block.
				   Right now, the expression block is at the head
				   of the loop body.  Once we've process the entire
				   body, we will move the expression block to the end */
				if(!jit_insn_branch(dpas_current_function(), &label))
				{
					dpas_out_of_memory();
				}

				/* Mark the start of the expression block */
				if(!jit_insn_label(dpas_current_function(), &label))
				{
					dpas_out_of_memory();
				}

				/* Push the label onto the loop stack */
				push_loop(label, jit_label_undefined, jit_label_undefined);

			}
    break;

  case 105:
#line 1906 "dpas-parser.y"
    {
				/* Test the expression and jump to the top of the body */
				if(!dpas_sem_is_error((yyvsp[(3) - (4)].semvalue)))
				{
					if(!jit_insn_branch_if
							(dpas_current_function(),
							 dpas_sem_get_value((yyvsp[(3) - (4)].semvalue)),
							 &(loop_stack[loop_stack_size - 1].top_label)))
					{
						dpas_out_of_memory();
					}
				}

				/* Mark the end of the expression block and the start
				   of the while loop's body.  This is also the end
				   of the code we'll need to move to the end */
				if(!jit_insn_label
						(dpas_current_function(),
						 &(loop_stack[loop_stack_size - 1].top_label)))
				{
					dpas_out_of_memory();
				}
			}
    break;

  case 106:
#line 1928 "dpas-parser.y"
    {

				/* Move the expression blocks down to this point */
				jit_insn_move_blocks_to_end
					(dpas_current_function(),
					 loop_stack[loop_stack_size - 1].expr_label,
					 loop_stack[loop_stack_size - 1].top_label);

				/* Define the "exit" label to this point in the code */
				if(loop_stack[loop_stack_size - 1].exit_label
						!= jit_label_undefined)
				{
					if(!jit_insn_label
							(dpas_current_function(),
							 &(loop_stack[loop_stack_size - 1].exit_label)))
					{
						dpas_out_of_memory();
					}
				}

				/* Pop the top-most entry from the loop stack */
				--loop_stack_size;
			}
    break;

  case 107:
#line 1954 "dpas-parser.y"
    {

				/* Define a label at the top of the loop body */
				jit_label_t label = jit_label_undefined;
				if(!jit_insn_label(dpas_current_function(), &label))
				{
					dpas_out_of_memory();
				}

				/* Push into a new loop context */
				push_loop(jit_label_undefined, label, jit_label_undefined);

			}
    break;

  case 108:
#line 1966 "dpas-parser.y"
    {

				/* Branch back to the top of the loop */
				if(!jit_insn_branch_if_not
						(dpas_current_function(),
						 dpas_sem_get_value((yyvsp[(6) - (6)].semvalue)),
						 &(loop_stack[loop_stack_size - 1].top_label)))
				{
					dpas_out_of_memory();
				}

				/* Set the label for the "exit" point of the loop */
				if(loop_stack[loop_stack_size - 1].exit_label
						!= jit_label_undefined)
				{
					if(!jit_insn_label
							(dpas_current_function(),
							 &(loop_stack[loop_stack_size - 1].exit_label)))
					{
						dpas_out_of_memory();
					}
				}

				/* Pop out of the current loop context */
				--loop_stack_size;
			}
    break;

  case 109:
#line 1995 "dpas-parser.y"
    {
				jit_type_t loop_type = jit_type_int;
				jit_value_t end_value;
				jit_label_t label = jit_label_undefined;
				jit_label_t label2 = jit_label_undefined;

				/* Validate the l-value and determine the loop variable type */
				if(dpas_sem_is_lvalue((yyvsp[(2) - (5)].semvalue)) || dpas_sem_is_lvalue_ea((yyvsp[(2) - (5)].semvalue)))
				{
					loop_type = dpas_sem_get_type((yyvsp[(2) - (5)].semvalue));
					if(!dpas_type_is_integer(loop_type))
					{
						dpas_error("`for' variables must be integer");
						loop_type = jit_type_int;
					}
				}
				else if(!dpas_sem_is_error((yyvsp[(2) - (5)].semvalue)))
				{
					dpas_error("invalid l-value in `for' statement");
				}

				/* TODO: type checking */

				/* Record the loop termination value in a temporary local */
				(yyvsp[(4) - (5)].semvalue) = dpas_lvalue_to_rvalue((yyvsp[(4) - (5)].semvalue));
				if(dpas_sem_is_rvalue((yyvsp[(4) - (5)].semvalue)))
				{
					if(jit_value_is_constant(dpas_sem_get_value((yyvsp[(4) - (5)].semvalue))))
					{
						end_value = dpas_sem_get_value((yyvsp[(4) - (5)].semvalue));
					}
					else
					{
						end_value = jit_value_create
							(dpas_current_function(), loop_type);
						if(!end_value)
						{
							dpas_out_of_memory();
						}
						if(!jit_insn_store
							(dpas_current_function(), end_value,
							 dpas_sem_get_value((yyvsp[(4) - (5)].semvalue))))
						{
							dpas_out_of_memory();
						}
					}
				}
				else
				{
					end_value = 0;
				}
				dpas_sem_set_rvalue((yyval.semvalue), loop_type, end_value);

				/* Jump to the beginning of the termination testing block */
				if(!jit_insn_branch(dpas_current_function(), &label))
				{
					dpas_out_of_memory();
				}

				/* Mark the head of the loop body */
				if(!jit_insn_label(dpas_current_function(), &label2))
				{
					dpas_out_of_memory();
				}

				/* Push the labels onto the loop stack */
				push_loop(label, label2, jit_label_undefined);

			}
    break;

  case 110:
#line 2063 "dpas-parser.y"
    {

				jit_value_t var_value;
				jit_value_t var2_value;
				jit_value_t test_value;

				/* Increment or decrement the loop counter */
				test_value = jit_value_create_nint_constant
					(dpas_current_function(), jit_type_int, (jit_nint)((yyvsp[(3) - (7)].direction)));
				if(!test_value)
				{
					dpas_out_of_memory();
				}
				if(dpas_sem_is_lvalue((yyvsp[(2) - (7)].semvalue)))
				{
					var_value = dpas_sem_get_value((yyvsp[(2) - (7)].semvalue));
					if(!jit_insn_store
							(dpas_current_function(), var_value,
							 jit_insn_add
							 	(dpas_current_function(),
								 var_value, test_value)))
					{
						dpas_out_of_memory();
					}
				}
				else if(dpas_sem_is_lvalue_ea((yyvsp[(2) - (7)].semvalue)))
				{
					var2_value = dpas_sem_get_value((yyvsp[(2) - (7)].semvalue));
					var_value = jit_insn_load_relative
						(dpas_current_function(), var2_value, 0,
						 dpas_sem_get_type((yyvsp[(2) - (7)].semvalue)));
					var_value = jit_insn_add
						(dpas_current_function(), var_value, test_value);
					if(!var_value)
					{
						dpas_out_of_memory();
					}
					if(!jit_insn_store_relative
						(dpas_current_function(), var2_value, 0,
						 jit_insn_convert
						 	(dpas_current_function(), var_value,
							 dpas_sem_get_type((yyvsp[(2) - (7)].semvalue)), 0)))
					{
						dpas_out_of_memory();
					}
				}
				else
				{
					var_value = 0;
				}

				/* Output the start of the termination testing block */
				if(!jit_insn_label
						(dpas_current_function(),
						 &(loop_stack[loop_stack_size - 1].expr_label)))
				{
					dpas_out_of_memory();
				}

				/* Reload the variable reference, if necessary */
				if(dpas_sem_is_lvalue_ea((yyvsp[(2) - (7)].semvalue)))
				{
					var_value = jit_insn_load_relative
						(dpas_current_function(), dpas_sem_get_value((yyvsp[(2) - (7)].semvalue)), 0,
						 dpas_sem_get_type((yyvsp[(2) - (7)].semvalue)));
				}

				/* Test the loop condition and branch back to the top */
				if(var_value)
				{
					if((yyvsp[(3) - (7)].direction) < 0)
					{
						test_value = jit_insn_ge
							(dpas_current_function(),
							 var_value, dpas_sem_get_value((yyvsp[(6) - (7)].semvalue)));
					}
					else
					{
						test_value = jit_insn_le
							(dpas_current_function(),
							 var_value, dpas_sem_get_value((yyvsp[(6) - (7)].semvalue)));
					}
					if(!test_value)
					{
						dpas_out_of_memory();
					}
					if(!jit_insn_branch_if
							(dpas_current_function(), test_value,
							 &(loop_stack[loop_stack_size - 1].top_label)))
					{
						dpas_out_of_memory();
					}
				}

				/* Set the position of the loop's "exit" label */
				if(loop_stack[loop_stack_size - 1].exit_label
						!= jit_label_undefined)
				{
					if(!jit_insn_label
							(dpas_current_function(),
							 &(loop_stack[loop_stack_size - 1].exit_label)))
					{
						dpas_out_of_memory();
					}
				}

				/* Pop out of the current loop context */
				--loop_stack_size;

			}
    break;

  case 111:
#line 2176 "dpas-parser.y"
    {
				/* TODO: type checking */
				(yyval.semvalue) = dpas_lvalue_to_rvalue((yyvsp[(1) - (1)].semvalue));
			}
    break;

  case 112:
#line 2183 "dpas-parser.y"
    { (yyval.direction) = 1; }
    break;

  case 113:
#line 2184 "dpas-parser.y"
    { (yyval.direction) = -1; }
    break;

  case 114:
#line 2188 "dpas-parser.y"
    {
				/* TODO */
				dpas_error("`case' statements not yet implemented");
			}
    break;

  case 118:
#line 2204 "dpas-parser.y"
    {}
    break;

  case 119:
#line 2205 "dpas-parser.y"
    {}
    break;

  case 120:
#line 2209 "dpas-parser.y"
    {}
    break;

  case 121:
#line 2210 "dpas-parser.y"
    {}
    break;

  case 122:
#line 2214 "dpas-parser.y"
    {
				/* TODO */
				dpas_error("`try' statements not yet implemented");
			}
    break;

  case 127:
#line 2235 "dpas-parser.y"
    { (yyval.semvalue) = (yyvsp[(1) - (1)].semvalue); }
    break;

  case 128:
#line 2236 "dpas-parser.y"
    {
				handle_compare_binary("=", jit_insn_eq, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 129:
#line 2239 "dpas-parser.y"
    {
				handle_compare_binary("<>", jit_insn_ne, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 130:
#line 2242 "dpas-parser.y"
    {
				handle_compare_binary("<", jit_insn_lt, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 131:
#line 2245 "dpas-parser.y"
    {
				handle_compare_binary(">", jit_insn_gt, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 132:
#line 2248 "dpas-parser.y"
    {
				handle_compare_binary("<=", jit_insn_le, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 133:
#line 2251 "dpas-parser.y"
    {
				handle_compare_binary(">=", jit_insn_ge, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 134:
#line 2254 "dpas-parser.y"
    {
				/* TODO */
			}
    break;

  case 135:
#line 2260 "dpas-parser.y"
    {
				(yyval.expr_list).exprs = 0;
				(yyval.expr_list).len = 0;
				expression_list_add(&((yyval.expr_list).exprs), &((yyval.expr_list).len), (yyvsp[(1) - (1)].semvalue));
			}
    break;

  case 136:
#line 2265 "dpas-parser.y"
    {
				(yyval.expr_list) = (yyvsp[(1) - (3)].expr_list);
				expression_list_add(&((yyval.expr_list).exprs), &((yyval.expr_list).len), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 137:
#line 2272 "dpas-parser.y"
    { (yyval.semvalue) = (yyvsp[(1) - (1)].semvalue); }
    break;

  case 138:
#line 2273 "dpas-parser.y"
    {
				if(!dpas_sem_is_rvalue((yyvsp[(2) - (2)].semvalue)) ||
				   !dpas_type_is_numeric(dpas_sem_get_type((yyvsp[(2) - (2)].semvalue))))
				{
					if(!dpas_sem_is_error((yyvsp[(2) - (2)].semvalue)))
					{
						dpas_error("invalid operand to unary `+'");
					}
					dpas_sem_set_error((yyval.semvalue));
				}
				else
				{
					(yyval.semvalue) = (yyvsp[(2) - (2)].semvalue);
				}
			}
    break;

  case 139:
#line 2288 "dpas-parser.y"
    {
				if(!dpas_sem_is_rvalue((yyvsp[(2) - (2)].semvalue)) ||
				   !dpas_type_is_numeric(dpas_sem_get_type((yyvsp[(2) - (2)].semvalue))))
				{
					if(!dpas_sem_is_error((yyvsp[(2) - (2)].semvalue)))
					{
						dpas_error("invalid operand to unary `-'");
					}
					dpas_sem_set_error((yyval.semvalue));
				}
				else
				{
					jit_value_t value;
					value = jit_insn_neg
						(dpas_current_function(),
						 dpas_sem_get_value(dpas_lvalue_to_rvalue((yyvsp[(2) - (2)].semvalue))));
					dpas_sem_set_rvalue((yyval.semvalue), jit_value_get_type(value), value);
				}
			}
    break;

  case 140:
#line 2310 "dpas-parser.y"
    { (yyval.semvalue) = (yyvsp[(1) - (1)].semvalue); }
    break;

  case 141:
#line 2311 "dpas-parser.y"
    {
				handle_binary("+", jit_insn_add, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 142:
#line 2314 "dpas-parser.y"
    {
				handle_binary("-", jit_insn_sub, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 143:
#line 2317 "dpas-parser.y"
    {
				if(dpas_sem_is_rvalue((yyvsp[(1) - (3)].semvalue)) &&
				   dpas_type_is_boolean(dpas_sem_get_type((yyvsp[(1) - (3)].semvalue))) &&
				   dpas_sem_is_rvalue((yyvsp[(3) - (3)].semvalue)) &&
				   dpas_type_is_boolean(dpas_sem_get_type((yyvsp[(3) - (3)].semvalue))))
				{
					/* Output code to compute a short-circuited "or" */
					jit_label_t label1 = jit_label_undefined;
					jit_label_t label2 = jit_label_undefined;
					jit_value_t value, const_value;
					(yyvsp[(1) - (3)].semvalue) = dpas_lvalue_to_rvalue((yyvsp[(1) - (3)].semvalue));
					(yyvsp[(3) - (3)].semvalue) = dpas_lvalue_to_rvalue((yyvsp[(3) - (3)].semvalue));
					if(!jit_insn_branch_if
							(dpas_current_function(),
							 dpas_sem_get_value((yyvsp[(1) - (3)].semvalue)), &label1))
					{
						dpas_out_of_memory();
					}
					if(!jit_insn_branch_if
							(dpas_current_function(),
							 dpas_sem_get_value((yyvsp[(3) - (3)].semvalue)), &label1))
					{
						dpas_out_of_memory();
					}
					value = jit_value_create
						(dpas_current_function(), jit_type_int);
					const_value = jit_value_create_nint_constant
						(dpas_current_function(), jit_type_int, 0);
					if(!value || !const_value)
					{
						dpas_out_of_memory();
					}
					if(!jit_insn_store(dpas_current_function(),
									   value, const_value))
					{
						dpas_out_of_memory();
					}
					if(!jit_insn_branch(dpas_current_function(), &label2))
					{
						dpas_out_of_memory();
					}
					if(!jit_insn_label(dpas_current_function(), &label1))
					{
						dpas_out_of_memory();
					}
					const_value = jit_value_create_nint_constant
						(dpas_current_function(), jit_type_int, 1);
					if(!const_value)
					{
						dpas_out_of_memory();
					}
					if(!jit_insn_store(dpas_current_function(),
									   value, const_value))
					{
						dpas_out_of_memory();
					}
					if(!jit_insn_label(dpas_current_function(), &label2))
					{
						dpas_out_of_memory();
					}
					dpas_sem_set_rvalue((yyval.semvalue), dpas_type_boolean, value);
				}
				else
				{
					handle_integer_binary("or", jit_insn_or, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
				}
			}
    break;

  case 144:
#line 2387 "dpas-parser.y"
    { (yyval.semvalue) = (yyvsp[(1) - (1)].semvalue); }
    break;

  case 145:
#line 2388 "dpas-parser.y"
    {
				handle_binary("*", jit_insn_mul, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 146:
#line 2391 "dpas-parser.y"
    {
				/* Standard Pascal always returns a floating-point
				   result for '/', but we don't do that here yet */
				handle_binary("/", jit_insn_div, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 147:
#line 2396 "dpas-parser.y"
    {
				handle_binary("div", jit_insn_div, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 148:
#line 2399 "dpas-parser.y"
    {
				handle_binary("mod", jit_insn_rem, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 149:
#line 2402 "dpas-parser.y"
    {
				if(dpas_sem_is_rvalue((yyvsp[(1) - (3)].semvalue)) &&
				   dpas_type_is_boolean(dpas_sem_get_type((yyvsp[(1) - (3)].semvalue))) &&
				   dpas_sem_is_rvalue((yyvsp[(3) - (3)].semvalue)) &&
				   dpas_type_is_boolean(dpas_sem_get_type((yyvsp[(3) - (3)].semvalue))))
				{
					/* Output code to compute a short-circuited "and" */
					jit_label_t label1 = jit_label_undefined;
					jit_label_t label2 = jit_label_undefined;
					jit_value_t value, const_value;
					(yyvsp[(1) - (3)].semvalue) = dpas_lvalue_to_rvalue((yyvsp[(1) - (3)].semvalue));
					(yyvsp[(3) - (3)].semvalue) = dpas_lvalue_to_rvalue((yyvsp[(3) - (3)].semvalue));
					if(!jit_insn_branch_if_not
							(dpas_current_function(),
							 dpas_sem_get_value((yyvsp[(1) - (3)].semvalue)), &label1))
					{
						dpas_out_of_memory();
					}
					if(!jit_insn_branch_if_not
							(dpas_current_function(),
							 dpas_sem_get_value((yyvsp[(3) - (3)].semvalue)), &label1))
					{
						dpas_out_of_memory();
					}
					value = jit_value_create
						(dpas_current_function(), jit_type_int);
					const_value = jit_value_create_nint_constant
						(dpas_current_function(), jit_type_int, 1);
					if(!value || !const_value)
					{
						dpas_out_of_memory();
					}
					if(!jit_insn_store(dpas_current_function(),
									   value, const_value))
					{
						dpas_out_of_memory();
					}
					if(!jit_insn_branch(dpas_current_function(), &label2))
					{
						dpas_out_of_memory();
					}
					if(!jit_insn_label(dpas_current_function(), &label1))
					{
						dpas_out_of_memory();
					}
					const_value = jit_value_create_nint_constant
						(dpas_current_function(), jit_type_int, 0);
					if(!const_value)
					{
						dpas_out_of_memory();
					}
					if(!jit_insn_store(dpas_current_function(),
									   value, const_value))
					{
						dpas_out_of_memory();
					}
					if(!jit_insn_label(dpas_current_function(), &label2))
					{
						dpas_out_of_memory();
					}
					dpas_sem_set_rvalue((yyval.semvalue), dpas_type_boolean, value);
				}
				else
				{
					handle_integer_binary("and", jit_insn_and, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
				}
			}
    break;

  case 150:
#line 2469 "dpas-parser.y"
    {
				handle_integer_binary("xor", jit_insn_xor, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 151:
#line 2472 "dpas-parser.y"
    {
				handle_integer_binary("shl", jit_insn_shl, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 152:
#line 2475 "dpas-parser.y"
    {
				handle_integer_binary("shr", jit_insn_shr, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 153:
#line 2481 "dpas-parser.y"
    { (yyval.semvalue) = (yyvsp[(1) - (1)].semvalue); }
    break;

  case 154:
#line 2482 "dpas-parser.y"
    {
				handle_binary("pow", jit_insn_pow, (yyvsp[(1) - (3)].semvalue), (yyvsp[(3) - (3)].semvalue));
			}
    break;

  case 155:
#line 2488 "dpas-parser.y"
    { (yyval.semvalue) = (yyvsp[(1) - (1)].semvalue); }
    break;

  case 156:
#line 2489 "dpas-parser.y"
    {
				jit_value_t value = jit_value_create_constant
					(dpas_current_function(), &((yyvsp[(1) - (1)].const_value)));
				dpas_sem_set_rvalue((yyval.semvalue), (yyvsp[(1) - (1)].const_value).type, value);
			}
    break;

  case 157:
#line 2494 "dpas-parser.y"
    {
				/* TODO */
				dpas_error("set expressions not yet implemented");
				dpas_sem_set_error((yyval.semvalue));
			}
    break;

  case 158:
#line 2499 "dpas-parser.y"
    {
				/* TODO */
				dpas_error("set expressions not yet implemented");
				dpas_sem_set_error((yyval.semvalue));
			}
    break;

  case 159:
#line 2504 "dpas-parser.y"
    {
				jit_value_t value;
				(yyvsp[(2) - (2)].semvalue) = dpas_lvalue_to_rvalue((yyvsp[(2) - (2)].semvalue));
				if(dpas_sem_is_rvalue((yyvsp[(2) - (2)].semvalue)) &&
				   dpas_type_is_boolean(dpas_sem_get_type((yyvsp[(2) - (2)].semvalue))))
				{
					value = jit_insn_to_not_bool
						(dpas_current_function(), dpas_sem_get_value((yyvsp[(2) - (2)].semvalue)));
					dpas_sem_set_rvalue((yyval.semvalue), dpas_type_boolean, value);
				}
				else if(dpas_sem_is_rvalue((yyvsp[(2) - (2)].semvalue)) &&
						dpas_type_is_integer(dpas_sem_get_type((yyvsp[(2) - (2)].semvalue))))
				{
					value = jit_insn_not
						(dpas_current_function(), dpas_sem_get_value((yyvsp[(2) - (2)].semvalue)));
					dpas_sem_set_rvalue((yyval.semvalue), jit_value_get_type(value), value);
				}
				else
				{
					if(!dpas_sem_is_error((yyvsp[(2) - (2)].semvalue)))
					{
						dpas_error("invalid operand to unary `not'");
					}
					dpas_sem_set_error((yyval.semvalue));
				}
			}
    break;

  case 160:
#line 2530 "dpas-parser.y"
    {
				jit_type_t type;
				if(dpas_sem_is_lvalue((yyvsp[(2) - (2)].semvalue)))
				{
					jit_value_t value;
					value = jit_insn_address_of
						(dpas_current_function(), dpas_sem_get_value((yyvsp[(2) - (2)].semvalue)));
					type = jit_type_create_pointer(dpas_sem_get_type((yyvsp[(2) - (2)].semvalue)), 1);
					if(!type)
					{
						dpas_out_of_memory();
					}
					dpas_sem_set_rvalue((yyval.semvalue), type, value);
				}
				else if(dpas_sem_is_lvalue_ea((yyvsp[(2) - (2)].semvalue)))
				{
					/* Turn the effective address into an r-value */
					type = jit_type_create_pointer(dpas_sem_get_type((yyvsp[(2) - (2)].semvalue)), 1);
					if(!type)
					{
						dpas_out_of_memory();
					}
					dpas_sem_set_rvalue((yyval.semvalue), type, dpas_sem_get_value((yyvsp[(2) - (2)].semvalue)));
				}
				else
				{
					if(!dpas_sem_is_error((yyvsp[(2) - (2)].semvalue)))
					{
						dpas_error("l-value required for address-of operator");
					}
					dpas_sem_set_error((yyval.semvalue));
				}
			}
    break;

  case 161:
#line 2563 "dpas-parser.y"
    {
				jit_type_t type;
				if(dpas_sem_is_lvalue((yyvsp[(2) - (2)].semvalue)))
				{
					jit_value_t value;
					value = jit_insn_address_of
						(dpas_current_function(), dpas_sem_get_value((yyvsp[(2) - (2)].semvalue)));
					type = jit_type_create_pointer(dpas_sem_get_type((yyvsp[(2) - (2)].semvalue)), 1);
					if(!type)
					{
						dpas_out_of_memory();
					}
					dpas_sem_set_rvalue((yyval.semvalue), jit_value_get_type(value), value);
				}
				else if(dpas_sem_is_lvalue_ea((yyvsp[(2) - (2)].semvalue)))
				{
					/* Turn the effective address into an r-value */
					type = jit_type_create_pointer(dpas_sem_get_type((yyvsp[(2) - (2)].semvalue)), 1);
					if(!type)
					{
						dpas_out_of_memory();
					}
					dpas_sem_set_rvalue((yyval.semvalue), type, dpas_sem_get_value((yyvsp[(2) - (2)].semvalue)));
				}
				else
				{
					if(!dpas_sem_is_error((yyvsp[(2) - (2)].semvalue)))
					{
						dpas_error("l-value required for address-of operator");
					}
					dpas_sem_set_error((yyval.semvalue));
				}
			}
    break;

  case 162:
#line 2596 "dpas-parser.y"
    { (yyval.semvalue) = (yyvsp[(2) - (3)].semvalue); }
    break;

  case 163:
#line 2597 "dpas-parser.y"
    {
				/* Call a function, with no ignored result */
				if(dpas_sem_is_builtin((yyvsp[(1) - (4)].semvalue)))
				{
					/* Expand a call to a builtin procedure */
					(yyval.semvalue) = dpas_expand_builtin
						(dpas_sem_get_builtin((yyvsp[(1) - (4)].semvalue)), (yyvsp[(3) - (4)].expr_list).exprs, (yyvsp[(3) - (4)].expr_list).len);
				}
				else if(dpas_sem_is_procedure((yyvsp[(1) - (4)].semvalue)))
				{
					/* Invoke a user-defined function */
					dpas_scope_item_t item = dpas_sem_get_procedure((yyvsp[(1) - (4)].semvalue));
					(yyval.semvalue) = invoke_procedure
						((jit_function_t)dpas_scope_item_info(item),
						 dpas_scope_item_name(item),
						 dpas_scope_item_type(item), 0, (yyvsp[(3) - (4)].expr_list).exprs, (yyvsp[(3) - (4)].expr_list).len);
				}
				else if(dpas_sem_is_rvalue((yyvsp[(1) - (4)].semvalue)) &&
						jit_type_is_signature(dpas_sem_get_type((yyvsp[(1) - (4)].semvalue))))
				{
					/* Invoke a function via an indirect pointer */
					(yyval.semvalue) = invoke_procedure
						(0, 0, dpas_sem_get_type((yyvsp[(1) - (4)].semvalue)), dpas_sem_get_value((yyvsp[(1) - (4)].semvalue)),
						 (yyvsp[(3) - (4)].expr_list).exprs, (yyvsp[(3) - (4)].expr_list).len);
				}
				else if(dpas_sem_is_type((yyvsp[(1) - (4)].semvalue)) && (yyvsp[(3) - (4)].expr_list).len == 1 &&
						dpas_sem_is_rvalue((yyvsp[(3) - (4)].expr_list).exprs[0]))
				{
					/* Cast a value to a new type */
					jit_value_t conv;
					conv = jit_insn_convert
						(dpas_current_function(),
						 dpas_sem_get_value(dpas_lvalue_to_rvalue((yyvsp[(3) - (4)].expr_list).exprs[0])),
						 dpas_sem_get_type((yyvsp[(1) - (4)].semvalue)), 0);
					if(!conv)
					{
						dpas_out_of_memory();
					}
					dpas_sem_set_rvalue((yyval.semvalue), dpas_sem_get_type((yyvsp[(1) - (4)].semvalue)), conv);
				}
				else
				{
					if(!dpas_sem_is_error((yyvsp[(1) - (4)].semvalue)))
					{
						dpas_error("invalid function name");
					}
					dpas_sem_set_error((yyval.semvalue));
				}
				expression_list_free((yyvsp[(3) - (4)].expr_list).exprs, (yyvsp[(3) - (4)].expr_list).len);
				if(dpas_sem_is_void((yyval.semvalue)))
				{
					dpas_error("cannot use a procedure in this context");
					dpas_sem_set_error((yyval.semvalue));
				}
			}
    break;

  case 164:
#line 2652 "dpas-parser.y"
    {
				/* TODO */
				dpas_error("`va_arg' not yet implemented");
				dpas_sem_set_error((yyval.semvalue));
			}
    break;

  case 165:
#line 2657 "dpas-parser.y"
    {
				jit_nuint size;
				jit_value_t value;
				if(dpas_sem_is_rvalue((yyvsp[(3) - (4)].semvalue)) || dpas_sem_is_type((yyvsp[(3) - (4)].semvalue)))
				{
					size = jit_type_get_size(dpas_sem_get_type((yyvsp[(3) - (4)].semvalue)));
					value = jit_value_create_nint_constant
						(dpas_current_function(), dpas_type_size_t,
						 (jit_nint)size);
					if(!value)
					{
						dpas_out_of_memory();
					}
					dpas_sem_set_rvalue((yyval.semvalue), dpas_type_size_t, value);
				}
				else
				{
					dpas_error("invalid operand to `sizeof'");
					dpas_sem_set_error((yyval.semvalue));
				}
			}
    break;

  case 166:
#line 2678 "dpas-parser.y"
    {
				/* TODO */
				dpas_error("ternary `if' not yet implemented");
				dpas_sem_set_error((yyval.semvalue));
			}
    break;

  case 167:
#line 2686 "dpas-parser.y"
    {
				dpas_scope_item_t item;
				int builtin;
				item = dpas_scope_lookup(dpas_scope_current(), (yyvsp[(1) - (1)].name), 1);
				if(!item)
				{
					builtin = dpas_is_builtin((yyvsp[(1) - (1)].name));
					if(!builtin)
					{
						dpas_error
							("`%s' is not declared in the current scope", (yyvsp[(1) - (1)].name));
						dpas_sem_set_error((yyval.semvalue));
					}
					else
					{
						dpas_sem_set_builtin((yyval.semvalue), builtin);
					}
				}
				else
				{
					switch(dpas_scope_item_kind(item))
					{
						case DPAS_ITEM_TYPE:
						{
							dpas_sem_set_type((yyval.semvalue), dpas_scope_item_type(item));
						}
						break;

						case DPAS_ITEM_VARIABLE:
						{
							dpas_sem_set_lvalue
								((yyval.semvalue), dpas_scope_item_type(item),
								 (jit_value_t)dpas_scope_item_info(item));
						}
						break;

						case DPAS_ITEM_GLOBAL_VARIABLE:
						{
							jit_value_t value;
							void *address = dpas_scope_item_info(item);
							value = jit_value_create_nint_constant
								(dpas_current_function(),
								 jit_type_void_ptr, (jit_nint)address);
							if(!value)
							{
								dpas_out_of_memory();
							}
							dpas_sem_set_lvalue_ea
								((yyval.semvalue), dpas_scope_item_type(item), value);
						}
						break;

						case DPAS_ITEM_CONSTANT:
						{
							jit_value_t const_value;
							const_value = jit_value_create_constant
								(dpas_current_function(),
								 (jit_constant_t *)dpas_scope_item_info(item));
							if(!const_value)
							{
								dpas_out_of_memory();
							}
							dpas_sem_set_rvalue
								((yyval.semvalue), dpas_scope_item_type(item), const_value);
						}
						break;

						case DPAS_ITEM_PROCEDURE:
						{
							dpas_sem_set_procedure
								((yyval.semvalue), dpas_scope_item_type(item), item);
						}
						break;

						case DPAS_ITEM_WITH:
						{
							/* TODO */
							dpas_sem_set_error((yyval.semvalue));
						}
						break;

						case DPAS_ITEM_FUNC_RETURN:
						{
							dpas_sem_set_return
								((yyval.semvalue), dpas_scope_item_type(item));
						}
						break;

						default:
						{
							dpas_sem_set_error((yyval.semvalue));
						}
						break;
					}
				}
				jit_free((yyvsp[(1) - (1)].name));
			}
    break;

  case 168:
#line 2783 "dpas-parser.y"
    {
				jit_value_t array = 0;
				jit_type_t array_type = 0;
				jit_type_t elem_type = 0;
				int rank = (yyvsp[(3) - (4)].expr_list).len;
				if(dpas_sem_is_lvalue((yyvsp[(1) - (4)].semvalue)) || dpas_sem_is_lvalue_ea((yyvsp[(1) - (4)].semvalue)))
				{
					elem_type = dpas_sem_get_type((yyvsp[(1) - (4)].semvalue));
					if(dpas_sem_is_lvalue_ea((yyvsp[(1) - (4)].semvalue)))
					{
						if(dpas_type_is_array(elem_type))
						{
							array_type = elem_type;
							array = dpas_sem_get_value((yyvsp[(1) - (4)].semvalue));
							rank = dpas_type_get_rank(elem_type);
							elem_type = dpas_type_get_elem(elem_type);
						}
						else if(dpas_type_is_conformant_array(elem_type))
						{
							array_type = elem_type;
							array = dpas_sem_get_value
								(dpas_lvalue_to_rvalue((yyvsp[(1) - (4)].semvalue)));
							rank = dpas_type_get_rank(elem_type);
							elem_type = dpas_type_get_elem(elem_type);
						}
						else if(jit_type_is_pointer(elem_type))
						{
							array = dpas_sem_get_value
								(dpas_lvalue_to_rvalue((yyvsp[(1) - (4)].semvalue)));
							rank = 1;
							elem_type = jit_type_get_ref(elem_type);
						}
						else
						{
							dpas_error("value is not an array");
						}
					}
					else
					{
						if(dpas_type_is_array(elem_type))
						{
							array_type = elem_type;
							array = jit_insn_address_of
								(dpas_current_function(),
								 dpas_sem_get_value((yyvsp[(1) - (4)].semvalue)));
							if(!array)
							{
								dpas_out_of_memory();
							}
							rank = dpas_type_get_rank(elem_type);
							elem_type = dpas_type_get_elem(elem_type);
						}
						else if(dpas_type_is_conformant_array(elem_type))
						{
							array_type = elem_type;
							array = dpas_sem_get_value((yyvsp[(1) - (4)].semvalue));
							rank = dpas_type_get_rank(elem_type);
							elem_type = dpas_type_get_elem(elem_type);
						}
						else if(jit_type_is_pointer(elem_type))
						{
							array = dpas_sem_get_value((yyvsp[(1) - (4)].semvalue));
							rank = 1;
							elem_type = jit_type_get_ref(elem_type);
						}
						else
						{
							dpas_error("value is not an array");
						}
					}
				}
				if(rank != (yyvsp[(3) - (4)].expr_list).len)
				{
					dpas_error("incorrect number of indices for array");
					dpas_sem_set_error((yyval.semvalue));
				}
				else if(array)
				{
					jit_nint i = 0;
					jit_function_t func = dpas_current_function();
					jit_value_t total_offset = 0;
					jit_value_t lvalue_ea = 0;
					jit_value_t index = 0;
					jit_value_t lower_bound = 0;
					jit_value_t upper_bound = 0;
					jit_value_t difference = 0;
					jit_value_t factor = 0;
					jit_value_t offset = 0;
					jit_value_t temp1 = 0;
					jit_value_t temp2 = 0;
					jit_value_t zero = 0;
					jit_label_t out_of_bounds = jit_label_undefined;
					jit_label_t all_is_well = jit_label_undefined;
					jit_nuint range_size = 1;
					dpas_array *info = 0;
					jit_type_t *bounds = 0;
	
					/* get the bounds from the tagged type that was created during array creation */
					/* may not be available if the array is accessed via a pointer */
					info = jit_type_get_tagged_data(array_type);
					if (info)
					{
						bounds = info->bounds;
					}

					/* create a constant jit_value_t that holds 0 */
					/* needed for comparision and initialization */
					zero = jit_value_create_nint_constant(func,jit_type_uint,0);

					/* initialize total_offset with zero */
					total_offset = jit_value_create(func,jit_type_uint);
					jit_insn_store(func,total_offset,zero);

					for ( i = 0 ; i < rank ; i++ )
					{
						/* get the value of the index from the expression list */
						index = dpas_sem_get_value((yyvsp[(3) - (4)].expr_list).exprs[i]);

						/* get values for upper and lower bounds */
						if ( bounds )
						{
							/* bounds can be either subrange or tagged */
							if ( jit_type_get_tagged_kind(bounds[i]) == DPAS_TAG_SUBRANGE )
							{
								upper_bound = jit_value_create_nint_constant(func,jit_type_int,
										((dpas_subrange *)jit_type_get_tagged_data(bounds[i]))->last.un.int_value);
								lower_bound = jit_value_create_nint_constant(func,jit_type_int,
										((dpas_subrange *)jit_type_get_tagged_data(bounds[i]))->first.un.int_value);
							}
							else if ( jit_type_get_tagged_kind(bounds[i]) == DPAS_TAG_ENUM )
							{
								upper_bound = jit_value_create_nint_constant(func,jit_type_int,
										((dpas_enum *)jit_type_get_tagged_data(bounds[i]))->num_elems-1);
								lower_bound = jit_value_create_nint_constant(func,jit_type_int,0);
							}

							/* check the upper bound first */
							temp1 = jit_insn_le(func,index,upper_bound);
							/* jump if not less than or equal to out_of_bounds */
							jit_insn_branch_if_not(func,temp1,&out_of_bounds);
							/* fall through if it is less than or equal */

							/* compute difference = index - lower_bound and check greater than 0 
								 so that we can re-use it */
							difference = jit_insn_sub(func,index,lower_bound);

							temp2 = jit_insn_ge(func,difference,zero);
							/* jump if not greater than or equal to out_of_bounds */
							jit_insn_branch_if_not(func,temp2,&out_of_bounds);
							/* fall through if greater than or equal */

							/* create a constant_value for the factor(range_size) */
							factor = jit_value_create_nint_constant(func,jit_type_uint,range_size);

							/* offset = difference * factor */
							offset = jit_insn_mul(func,difference,factor);

							/* total_offset += offset */
							total_offset = jit_insn_add(func,total_offset,offset);

							/*compute the range size for the next dimension */
							range_size *= (jit_value_get_nint_constant(upper_bound) - 
										(jit_value_get_nint_constant(lower_bound) -1));
						}
						else
						{
							/* no bounds are available, so it must be a pointer access */
							jit_insn_store(func,total_offset,index);
						}
					}

					if ( bounds )
					{
						/* if anything went wrong in the loop, we would be in out_of_bounds. 
							 so jump to all_is_well */
						jit_insn_branch(func,&all_is_well);

						/* if we are here, out_of_bounds, throw an exception */
						jit_insn_label(func,&out_of_bounds);

						throw_builtin_exception(func, JIT_RESULT_OUT_OF_BOUNDS);

						/* if we we are here, all_is_well */
						jit_insn_label(func,&all_is_well);
					}

					/* compute effective address and set lvalue_ea*/
					lvalue_ea = jit_insn_load_elem_address(func,array,total_offset,elem_type);
					dpas_sem_set_lvalue_ea((yyval.semvalue),elem_type,lvalue_ea);

					/* clean-up : we aren't allocating anything here */
				}
				else
				{
					dpas_error("invalid l-value supplied to array expression");
					dpas_sem_set_error((yyval.semvalue));
				}
				expression_list_free((yyvsp[(3) - (4)].expr_list).exprs, (yyvsp[(3) - (4)].expr_list).len);
			}
    break;

  case 169:
#line 2982 "dpas-parser.y"
    {
				/* Fetch the effective address of a record field */
				jit_type_t type = dpas_sem_get_type((yyvsp[(1) - (3)].semvalue));
				jit_type_t field_type;
				jit_value_t address;
				jit_nint offset;
				if(dpas_sem_is_lvalue_ea((yyvsp[(1) - (3)].semvalue)))
				{
					address = dpas_sem_get_value((yyvsp[(1) - (3)].semvalue));
				}
				else if(dpas_sem_is_lvalue((yyvsp[(1) - (3)].semvalue)))
				{
					address = jit_insn_address_of
						(dpas_current_function(), dpas_sem_get_value((yyvsp[(1) - (3)].semvalue)));
					if(!address)
					{
						dpas_out_of_memory();
					}
				}
				else
				{
					if(!dpas_sem_is_error((yyvsp[(1) - (3)].semvalue)))
					{
						dpas_error("invalid left hand side for `.'");
					}
					type = 0;
					address = 0;
				}
				if(type && dpas_type_is_record(type))
				{
					field_type = dpas_type_get_field(type, (yyvsp[(3) - (3)].name), &offset);
					if(field_type)
					{
						if(offset != 0)
						{
							address = jit_insn_add_relative
								(dpas_current_function(), address, offset);
							if(!address)
							{
								dpas_out_of_memory();
							}
						}
						dpas_sem_set_lvalue_ea((yyval.semvalue), field_type, address);
					}
					else
					{
						char *name = dpas_type_name(type);
						dpas_error("`%s' is not a member of `%s'", (yyvsp[(3) - (3)].name), name);
						jit_free(name);
						dpas_sem_set_error((yyval.semvalue));
					}
				}
				else if(type)
				{
					char *name = dpas_type_name(type);
					dpas_error("`%s' is not a record type", name);
					jit_free(name);
					dpas_sem_set_error((yyval.semvalue));
				}
				else
				{
					dpas_sem_set_error((yyval.semvalue));
				}
				jit_free((yyvsp[(3) - (3)].name));
			}
    break;

  case 170:
#line 3047 "dpas-parser.y"
    {
				/* Dereference a pointer value */
				jit_value_t value;
				if(!jit_type_is_pointer(dpas_sem_get_type((yyvsp[(1) - (2)].semvalue))))
				{
					if(!dpas_sem_is_error((yyvsp[(1) - (2)].semvalue)))
					{
						dpas_error("invalid operand to unary `^'");
					}
					dpas_sem_set_error((yyval.semvalue));
				}
				else if(dpas_sem_is_lvalue((yyvsp[(1) - (2)].semvalue)) || dpas_sem_is_rvalue((yyvsp[(1) - (2)].semvalue)))
				{
					/* Turn the pointer value into an effective address */
					value = jit_insn_add_relative
						(dpas_current_function(), dpas_sem_get_value((yyvsp[(1) - (2)].semvalue)), 0);
					if(!value)
					{
						dpas_out_of_memory();
					}
					dpas_sem_set_lvalue_ea
						((yyval.semvalue), jit_type_get_ref(dpas_sem_get_type((yyvsp[(1) - (2)].semvalue))), value);
				}
				else if(dpas_sem_is_lvalue_ea((yyvsp[(1) - (2)].semvalue)))
				{
					/* Fetch the pointer value and construct a new adddress */
					value = jit_insn_load_relative
						(dpas_current_function(), dpas_sem_get_value((yyvsp[(1) - (2)].semvalue)),
						 0, jit_type_void_ptr);
					if(!value)
					{
						dpas_out_of_memory();
					}
					dpas_sem_set_lvalue_ea
						((yyval.semvalue), jit_type_get_ref(dpas_sem_get_type((yyvsp[(1) - (2)].semvalue))), value);
				}
				else
				{
					if(!dpas_sem_is_error((yyvsp[(1) - (2)].semvalue)))
					{
						dpas_error("invalid operand to unary `^'");
					}
					dpas_sem_set_error((yyval.semvalue));
				}
			}
    break;

  case 171:
#line 3099 "dpas-parser.y"
    {
				dpas_scope_item_t item;
				item = dpas_scope_lookup(dpas_scope_current(), (yyvsp[(1) - (1)].name), 1);
				if(!item)
				{
					dpas_undeclared((yyvsp[(1) - (1)].name));
					(yyval.type) = jit_type_void;
				}
				else if(dpas_scope_item_kind(item) != DPAS_ITEM_TYPE)
				{
					dpas_error("`%s' does not refer to a type in the "
							   "current scope", (yyvsp[(1) - (1)].name));
					(yyval.type) = jit_type_void;
				}
				else
				{
					(yyval.type) = jit_type_copy(dpas_scope_item_type(item));
				}
				jit_free((yyvsp[(1) - (1)].name));
			}
    break;

  case 172:
#line 3122 "dpas-parser.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 173:
#line 3123 "dpas-parser.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 174:
#line 3124 "dpas-parser.y"
    { (yyval.type) = (yyvsp[(2) - (2)].type); }
    break;

  case 175:
#line 3128 "dpas-parser.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 176:
#line 3129 "dpas-parser.y"
    {
				jit_type_t type;
				int posn;
				dpas_scope_item_t item;
				jit_constant_t value;

				/* Create the enumerated type */
				type = dpas_create_enum(jit_type_int, (yyvsp[(2) - (3)].id_list).len);

				/* Declare all of the identifiers into the current scope
				   as constants whose values correspond to the positions */
				for(posn = 0; posn < (yyvsp[(2) - (3)].id_list).len; ++posn)
				{
					if(!((yyvsp[(2) - (3)].id_list).list[posn]))
					{
						/* Placeholder for a duplicate identifier.  The error
						   was already reported inside "IdentifierList" */
						continue;
					}
					item = dpas_scope_lookup(dpas_scope_current(),
											 (yyvsp[(2) - (3)].id_list).list[posn], 0);
					if(item)
					{
						dpas_redeclared((yyvsp[(2) - (3)].id_list).list[posn], item);
						continue;
					}
					value.type = type;
					value.un.int_value = (jit_int)posn;
					dpas_scope_add_const(dpas_scope_current(),
										(yyvsp[(2) - (3)].id_list).list[posn], &value,
										dpas_filename, dpas_linenum);
				}

				/* Free the identifier list, which we no longer need */
				identifier_list_free((yyvsp[(2) - (3)].id_list).list, (yyvsp[(2) - (3)].id_list).len);

				/* Return the type as our semantic value */
				(yyval.type) = type;
			}
    break;

  case 177:
#line 3168 "dpas-parser.y"
    {
				/* Infer a common type for the subrange */
				jit_type_t type = dpas_common_type((yyvsp[(1) - (3)].const_value).type, (yyvsp[(3) - (3)].const_value).type, 1);
				if(type)
				{
					/* TODO: check that value1 <= value2 */
					dpas_subrange range;
					dpas_convert_constant(&(range.first), &((yyvsp[(1) - (3)].const_value)), type);
					dpas_convert_constant(&(range.last), &((yyvsp[(3) - (3)].const_value)), type);
					(yyval.type) = dpas_create_subrange(type, &range);
					jit_type_free((yyvsp[(1) - (3)].const_value).type);
					jit_type_free((yyvsp[(3) - (3)].const_value).type);
				}
				else
				{
					char *name1 = dpas_type_name((yyvsp[(1) - (3)].const_value).type);
					char *name2 = dpas_type_name((yyvsp[(3) - (3)].const_value).type);
					if(!jit_strcmp(name1, name2))
					{
						dpas_error("cannot declare a subrange within `%s'",
								   name1);
					}
					else
					{
						dpas_error("cannot declare a subrange within "
								   "`%s' or `%s'", name1, name2);
					}
					jit_free(name1);
					jit_free(name2);
					(yyval.type) = (yyvsp[(1) - (3)].const_value).type;
					jit_type_free((yyvsp[(3) - (3)].const_value).type);
				}
			}
    break;

  case 178:
#line 3204 "dpas-parser.y"
    {
				(yyval.type) = dpas_create_array((yyvsp[(3) - (6)].type_list).list, (yyvsp[(3) - (6)].type_list).len, (yyvsp[(6) - (6)].type));
			}
    break;

  case 179:
#line 3207 "dpas-parser.y"
    {
				jit_type_t type;
				type = jit_type_create_struct
					((yyvsp[(2) - (3)].parameters).types, (unsigned int)((yyvsp[(2) - (3)].parameters).len), 1);
				if(!type)
				{
					dpas_out_of_memory();
				}
				if(!jit_type_set_names
						(type, (yyvsp[(2) - (3)].parameters).names, (unsigned int)((yyvsp[(2) - (3)].parameters).len)))
				{
					dpas_out_of_memory();
				}
				type = jit_type_create_tagged(type, DPAS_TAG_NAME, 0, 0, 0);
				parameter_list_free(&((yyvsp[(2) - (3)].parameters)));
				(yyval.type) = type;
			}
    break;

  case 180:
#line 3224 "dpas-parser.y"
    {
				if(!dpas_is_set_compatible((yyvsp[(3) - (3)].type)))
				{
					char *name = dpas_type_name((yyvsp[(3) - (3)].type));
					dpas_error("`%s' cannot be used as the member type "
							   "for a set", name);
					jit_free(name);
				}
				(yyval.type) = jit_type_create_tagged
						(jit_type_uint, DPAS_TAG_SET,
						 (yyvsp[(3) - (3)].type), (jit_meta_free_func)jit_type_free, 0);
			}
    break;

  case 181:
#line 3236 "dpas-parser.y"
    {
				dpas_scope_item_t item;
				item = dpas_scope_lookup(dpas_scope_current(), (yyvsp[(2) - (2)].name), 1);
				if(!item)
				{
					/* The name is not declared yet, so it is probably a
					   forward reference to some later record type.  We need
					   to add a placeholder for the later definition */
					char *name;
					name = jit_strdup((yyvsp[(2) - (2)].name));
					if(!name)
					{
						dpas_out_of_memory();
					}
					(yyval.type) = jit_type_create_tagged(0, DPAS_TAG_NAME,
												name, jit_free, 0);
					if(!((yyval.type)))
					{
						dpas_out_of_memory();
					}
					dpas_scope_add(dpas_scope_current(), (yyvsp[(2) - (2)].name), (yyval.type),
								   DPAS_ITEM_TYPE, 0, 0,
								   dpas_filename, dpas_linenum);
				}
				else if(dpas_scope_item_kind(item) != DPAS_ITEM_TYPE)
				{
					dpas_error("`%s' does not refer to a type in the "
							   "current scope", (yyvsp[(2) - (2)].name));
					(yyval.type) = jit_type_void;
				}
				else
				{
					(yyval.type) = jit_type_copy(dpas_scope_item_type(item));
				}
				(yyval.type) = jit_type_create_pointer((yyval.type), 0);
				if(!((yyval.type)))
				{
					dpas_out_of_memory();
				}
				jit_free((yyvsp[(2) - (2)].name));
			}
    break;

  case 182:
#line 3280 "dpas-parser.y"
    {
				(yyval.type_list).list = 0;
				(yyval.type_list).len = 0;
				type_list_add(&((yyval.type_list).list), &((yyval.type_list).len), (yyvsp[(1) - (1)].type));
			}
    break;

  case 183:
#line 3285 "dpas-parser.y"
    {
				(yyval.type_list) = (yyvsp[(1) - (3)].type_list);
				type_list_add(&((yyval.type_list).list), &((yyval.type_list).len), (yyvsp[(3) - (3)].type));
			}
    break;

  case 184:
#line 3292 "dpas-parser.y"
    {
				/* The type must be an enumeration or integer subrange */
				if(jit_type_get_tagged_kind((yyvsp[(1) - (1)].type)) == DPAS_TAG_ENUM)
				{
					(yyval.type) = (yyvsp[(1) - (1)].type);
				}
				else if(jit_type_get_tagged_kind((yyvsp[(1) - (1)].type)) == DPAS_TAG_SUBRANGE &&
						jit_type_get_tagged_type((yyvsp[(1) - (1)].type)) == jit_type_int)
				{
					(yyval.type) = (yyvsp[(1) - (1)].type);
				}
				else
				{
					char *name = dpas_type_name((yyvsp[(1) - (1)].type));
					dpas_error("`%s' cannot be used as an array bound", name);
					jit_free(name);
					(yyval.type) = 0;
				}
			}
    break;

  case 185:
#line 3314 "dpas-parser.y"
    { parameter_list_init(&((yyval.parameters))); }
    break;

  case 186:
#line 3315 "dpas-parser.y"
    { (yyval.parameters) = (yyvsp[(1) - (1)].parameters); }
    break;

  case 187:
#line 3316 "dpas-parser.y"
    { (yyval.parameters) = (yyvsp[(1) - (2)].parameters); }
    break;

  case 188:
#line 3317 "dpas-parser.y"
    {
				(yyval.parameters) = (yyvsp[(1) - (3)].parameters);
				parameter_list_merge(&((yyval.parameters)), &((yyvsp[(3) - (3)].parameters)));
			}
    break;

  case 189:
#line 3321 "dpas-parser.y"
    {
				(yyval.parameters) = (yyvsp[(1) - (4)].parameters);
				parameter_list_merge(&((yyval.parameters)), &((yyvsp[(3) - (4)].parameters)));
			}
    break;

  case 190:
#line 3325 "dpas-parser.y"
    { (yyval.parameters) = (yyvsp[(1) - (1)].parameters); }
    break;

  case 191:
#line 3326 "dpas-parser.y"
    { (yyval.parameters) = (yyvsp[(1) - (2)].parameters); }
    break;

  case 192:
#line 3330 "dpas-parser.y"
    { (yyval.parameters) = (yyvsp[(1) - (1)].parameters); }
    break;

  case 193:
#line 3331 "dpas-parser.y"
    {
				(yyval.parameters) = (yyvsp[(1) - (3)].parameters);
				parameter_list_merge(&((yyval.parameters)), &((yyvsp[(3) - (3)].parameters)));
			}
    break;

  case 194:
#line 3338 "dpas-parser.y"
    {
				parameter_list_create(&((yyval.parameters)), (yyvsp[(1) - (3)].id_list).list, (yyvsp[(1) - (3)].id_list).len, (yyvsp[(3) - (3)].type));
				jit_type_free((yyvsp[(3) - (3)].type));
			}
    break;

  case 195:
#line 3342 "dpas-parser.y"
    {
				parameter_list_init(&((yyval.parameters)));
				parameter_list_add(&((yyval.parameters)), (yyvsp[(1) - (1)].procedure).name, (yyvsp[(1) - (1)].procedure).type);
			}
    break;

  case 196:
#line 3349 "dpas-parser.y"
    {
				parameter_list_init(&((yyval.parameters)));
				parameter_list_add(&((yyval.parameters)), (yyvsp[(2) - (6)].name), (yyvsp[(4) - (6)].type));
				parameter_list_add(&((yyval.parameters)), 0, (yyvsp[(6) - (6)].type));
			}
    break;

  case 197:
#line 3354 "dpas-parser.y"
    {
				parameter_list_init(&((yyval.parameters)));
				parameter_list_add(&((yyval.parameters)), 0, (yyvsp[(5) - (5)].type));
				jit_type_free((yyvsp[(3) - (5)].type));
			}
    break;

  case 198:
#line 3362 "dpas-parser.y"
    {
				/* Create a union with all of the case limbs */
				(yyval.type) = jit_type_create_union
					((yyvsp[(1) - (1)].type_list).list, (unsigned int)((yyvsp[(1) - (1)].type_list).len), 0);
				jit_free((yyvsp[(1) - (1)].type_list).list);
			}
    break;

  case 199:
#line 3371 "dpas-parser.y"
    {
				(yyval.type_list).list = 0;
				(yyval.type_list).len = 0;
				type_list_add(&((yyval.type_list).list), &((yyval.type_list).len), (yyvsp[(1) - (1)].type));
			}
    break;

  case 200:
#line 3376 "dpas-parser.y"
    {
				(yyval.type_list) = (yyvsp[(1) - (3)].type_list);
				type_list_add(&((yyval.type_list).list), &((yyval.type_list).len), (yyvsp[(3) - (3)].type));
			}
    break;

  case 201:
#line 3383 "dpas-parser.y"
    {
				jit_type_t type;
				type = jit_type_create_struct
					((yyvsp[(4) - (5)].parameters).types, (unsigned int)((yyvsp[(4) - (5)].parameters).len), 1);
				if(!type)
				{
					dpas_out_of_memory();
				}
				if(!jit_type_set_names
						(type, (yyvsp[(4) - (5)].parameters).names, (unsigned int)((yyvsp[(4) - (5)].parameters).len)))
				{
					dpas_out_of_memory();
				}
				parameter_list_free(&((yyvsp[(4) - (5)].parameters)));
				(yyval.type) = type;
			}
    break;

  case 202:
#line 3404 "dpas-parser.y"
    {}
    break;

  case 203:
#line 3405 "dpas-parser.y"
    {}
    break;

  case 204:
#line 3413 "dpas-parser.y"
    { (yyval.const_value) = (yyvsp[(1) - (1)].const_value); }
    break;

  case 205:
#line 3414 "dpas-parser.y"
    {
				if((yyvsp[(2) - (2)].const_value).type != jit_type_int &&
				   (yyvsp[(2) - (2)].const_value).type != jit_type_uint &&
				   (yyvsp[(2) - (2)].const_value).type != jit_type_long &&
				   (yyvsp[(2) - (2)].const_value).type != jit_type_ulong &&
				   (yyvsp[(2) - (2)].const_value).type != jit_type_nfloat)
				{
					char *name = dpas_type_name((yyvsp[(2) - (2)].const_value).type);
					dpas_error("unary `+' cannot be applied to a constant "
							   "of type `%s'", name);
					jit_free(name);
				}
				(yyval.const_value) = (yyvsp[(2) - (2)].const_value);
			}
    break;

  case 206:
#line 3428 "dpas-parser.y"
    {
				if((yyvsp[(2) - (2)].const_value).type == jit_type_int)
				{
					(yyval.const_value).type = (yyvsp[(2) - (2)].const_value).type;
					(yyval.const_value).un.int_value = -((yyvsp[(2) - (2)].const_value).un.int_value);
				}
				else if((yyvsp[(2) - (2)].const_value).type == jit_type_uint)
				{
					(yyval.const_value).type = jit_type_long;
					(yyval.const_value).un.long_value = -((jit_long)((yyvsp[(2) - (2)].const_value).un.uint_value));
				}
				else if((yyvsp[(2) - (2)].const_value).type == jit_type_long)
				{
					(yyval.const_value).type = jit_type_long;
					(yyval.const_value).un.long_value = -((yyvsp[(2) - (2)].const_value).un.long_value);
				}
				else if((yyvsp[(2) - (2)].const_value).type == jit_type_ulong)
				{
					(yyval.const_value).type = jit_type_long;
					(yyval.const_value).un.long_value = -((jit_long)((yyvsp[(2) - (2)].const_value).un.ulong_value));
				}
				else if((yyvsp[(2) - (2)].const_value).type == jit_type_nfloat)
				{
					(yyval.const_value).type = jit_type_nfloat;
					(yyval.const_value).un.nfloat_value = -((yyvsp[(2) - (2)].const_value).un.nfloat_value);
				}
				else
				{
					char *name = dpas_type_name((yyvsp[(2) - (2)].const_value).type);
					dpas_error("unary `-' cannot be applied to a constant "
							   "of type `%s'", name);
					jit_free(name);
					(yyval.const_value) = (yyvsp[(2) - (2)].const_value);
				}
			}
    break;

  case 207:
#line 3466 "dpas-parser.y"
    { (yyval.const_value) = (yyvsp[(1) - (1)].const_value); }
    break;

  case 208:
#line 3467 "dpas-parser.y"
    {
				dpas_scope_item_t item;
				item = dpas_scope_lookup(dpas_scope_current(), (yyvsp[(1) - (1)].name), 1);
				if(!item)
				{
					dpas_error("`%s' is not declared in the current scope", (yyvsp[(1) - (1)].name));
					(yyval.const_value).type = jit_type_int;
					(yyval.const_value).un.int_value = 0;
				}
				else if(dpas_scope_item_kind(item) != DPAS_ITEM_CONSTANT)
				{
					dpas_error("`%s' is not declared as a constant "
							   "in the current scope", (yyvsp[(1) - (1)].name));
					(yyval.const_value).type = jit_type_int;
					(yyval.const_value).un.int_value = 0;
				}
				else
				{
					(yyval.const_value) = *((jit_constant_t *)(dpas_scope_item_info(item)));
				}
				jit_free((yyvsp[(1) - (1)].name));
			}
    break;

  case 209:
#line 3492 "dpas-parser.y"
    {
				(yyval.const_value).type = (yyvsp[(1) - (1)].int_const).type;
				if((yyvsp[(1) - (1)].int_const).type == jit_type_int)
				{
					(yyval.const_value).un.int_value = (jit_int)((yyvsp[(1) - (1)].int_const).value);
				}
				else if((yyvsp[(1) - (1)].int_const).type == jit_type_uint)
				{
					(yyval.const_value).un.uint_value = (jit_uint)((yyvsp[(1) - (1)].int_const).value);
				}
				else if((yyvsp[(1) - (1)].int_const).type == jit_type_long)
				{
					(yyval.const_value).un.long_value = (jit_long)((yyvsp[(1) - (1)].int_const).value);
				}
				else
				{
					(yyval.const_value).un.ulong_value = (yyvsp[(1) - (1)].int_const).value;
				}
			}
    break;

  case 210:
#line 3511 "dpas-parser.y"
    {
				(yyval.const_value).type = jit_type_nfloat;
				(yyval.const_value).un.nfloat_value = (yyvsp[(1) - (1)].real_const);
			}
    break;

  case 211:
#line 3515 "dpas-parser.y"
    {
				/* Note: the string pointer leaks from the parser,
				   but since we probably need it to hang around for
				   runtime, this shouldn't be serious */
				(yyval.const_value).type = dpas_type_string;
				(yyval.const_value).un.ptr_value = (yyvsp[(1) - (1)].name);
			}
    break;

  case 212:
#line 3522 "dpas-parser.y"
    {
				(yyval.const_value).type = dpas_type_nil;
				(yyval.const_value).un.ptr_value = 0;
			}
    break;


/* Line 1267 of yacc.c.  */
#line 5593 "dpas-parser.c"
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



