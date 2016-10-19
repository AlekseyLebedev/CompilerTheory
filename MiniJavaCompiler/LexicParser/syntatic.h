/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_C_PROJECTS_COMPILERTHEORY_MINIJAVACOMPILER_LEXICPARSER_SYNTATIC_H_INCLUDED
# define YY_YY_C_PROJECTS_COMPILERTHEORY_MINIJAVACOMPILER_LEXICPARSER_SYNTATIC_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_NUM = 258,
     T_ID = 259,
     T_class = 260,
     T_public = 261,
     T_private = 262,
     T_static = 263,
     T_main = 264,
     T_extends = 265,
     T_return = 266,
     T_new = 267,
     T_void = 268,
     T_int = 269,
     T_boolean = 270,
     T_string = 271,
     T_dot = 272,
     T_else = 273,
     T_star = 274,
     T_lparen = 275,
     T_rparen = 276,
     T_lbrace = 277,
     T_rbrace = 278,
     T_lbracket = 279,
     T_rbracket = 280,
     T_if = 281,
     T_while = 282,
     T_sop = 283,
     T_length = 284,
     T_true = 285,
     T_false = 286,
     T_this = 287,
     T_equal = 288,
     T_and = 289,
     T_less = 290,
     T_plus = 291,
     T_minus = 292,
     T_times = 293,
     T_divide = 294,
     T_mod = 295,
     T_or = 296,
     T_semi = 297,
     T_comma = 298,
     T_not = 299
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 22 "C:\\Projects\\CompilerTheory\\MiniJavaCompiler\\LexicParser\\syntatic.txt"

	int int_val;
	std::string str_val;
	std::shared_ptr<CProgram> program;
	std::shared_ptr<CMainClass> mainClass;
	std::shared_ptr<CClassDeclarationList> classDeclarationList;
	std::shared_ptr<CClassDeclaration> classDeclaration;
	std::shared_ptr<CClassExtend> classExtend;
	std::shared_ptr<CVarDeclarationList> varDeclarationList;
	std::shared_ptr<CVarDeclaration> varDeclaration;
	std::shared_ptr<CMethodDeclarationList> methodDeclarationList;
	std::shared_ptr<CMethodDeclaration> methodDeclaration;
	std::shared_ptr<CType> type;
	std::shared_ptr<CExpressionList> expressionList;
	std::shared_ptr<IExpression> expression;
	std::shared_ptr<CStatementList> statementList;
	std::shared_ptr<IStatement> statement;
	std::shared_ptr<CArgumentList> argumentList;
	std::shared_ptr<CArgument> argument;


/* Line 2058 of yacc.c  */
#line 123 "C:\\Projects\\CompilerTheory\\MiniJavaCompiler\\LexicParser\\syntatic.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_C_PROJECTS_COMPILERTHEORY_MINIJAVACOMPILER_LEXICPARSER_SYNTATIC_H_INCLUDED  */
