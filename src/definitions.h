/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_SRC_DEFINITIONS_H_INCLUDED
# define YY_YY_SRC_DEFINITIONS_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_AS = 258,
    TK_CHAR = 259,
    TK_ELSE = 260,
    TK_FLOAT = 261,
    TK_IF = 262,
    TK_INT = 263,
    TK_NEW = 264,
    TK_RETURN = 265,
    TK_BOOL = 266,
    TK_WHILE = 267,
    TK_ID = 268,
    TK_STRING = 269,
    TK_INTEGER = 270,
    TK_FLOATING = 271,
    TK_EQ = 272,
    TK_NE = 273,
    TK_LE = 274,
    TK_GE = 275,
    TK_AND = 276,
    TK_OR = 277,
    TK_FALSE = 278,
    TK_TRUE = 279
  };
#endif
/* Tokens.  */
#define TK_AS 258
#define TK_CHAR 259
#define TK_ELSE 260
#define TK_FLOAT 261
#define TK_IF 262
#define TK_INT 263
#define TK_NEW 264
#define TK_RETURN 265
#define TK_BOOL 266
#define TK_WHILE 267
#define TK_ID 268
#define TK_STRING 269
#define TK_INTEGER 270
#define TK_FLOATING 271
#define TK_EQ 272
#define TK_NE 273
#define TK_LE 274
#define TK_GE 275
#define TK_AND 276
#define TK_OR 277
#define TK_FALSE 278
#define TK_TRUE 279

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "../src/monga_grammar.y" /* yacc.c:1909  */

  int i;
  double d;
  char *s;
  Node *n;

#line 109 "../src/definitions.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_DEFINITIONS_H_INCLUDED  */
