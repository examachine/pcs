/*
**
** Interface of lexical and syntax analyzers
**
*/

#include <stdio.h>

#include "Context.hxx"

extern int yylex();
extern FILE *yyin;
extern int line_number;
extern int yyparse();
extern int yydebug;
