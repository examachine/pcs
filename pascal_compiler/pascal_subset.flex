/*
** Lexical analyzer for compiler
**
** Flex source
**
** exa/analog
**
*/


%{
#include "General.hxx"
#include <ctype.h>
#include <iostream.h>
#include "pascal_subset.hxx"
#include "pascal_subset.tab.h"
int line_number = 1;
%}

/* Options */

%option never-interactive stack
%option nodefault
%option nodebug

/* Regular Definitions */

digit		[0-9]
digits		{digit}+
alpha		[A-Za-z\_]
alphanum	[0-9A-Za-z\_]

lit_int		{digits}
lit_float	{digits}(\.{digits})?(E[+-]?{digits})?
id		{alpha}{alphanum}*

punctuation     [\(\)\[\],:;\.]

/* REs that are removed from the source file */
white_space	[ \t]+

/* keyword successor */
ks		[ \t\n\(\)\[\],:;\.]

/* Start Conditions */
/* exclusive */
%x keyword non_keyword comment

/* Rules */

%%
.			yyless(0); BEGIN(keyword); 

<keyword>{
program/{ks}		return PROGRAM;
var/{ks}		return VAR;
array/{ks}		return ARRAY;
of/{ks}		        return OF;
integer/{ks}		return INTEGER;
real/{ks}		return REAL;
function/{ks}		return FUNCTION;
procedure/{ks}		return PROCEDURE;
begin/{ks}		return BLOCK_BEG;
end/{ks}		return BLOCK_END;
if/{ks}			return IF;
then/{ks}		return THEN;
else/{ks}		return ELSE;
while/{ks}		return WHILE;
do/{ks}			return DO;
\n                      line_number++;
{white_space}           /* consume white_space */
.			yyless(0); BEGIN(non_keyword);
}


<non_keyword>{

  {lit_int}		yylval.integer = atoi(yytext); return L_INT;
  {lit_float}		yylval.floating = atof(yytext); return L_FLOAT;

  \(			return LP;
  \)			return RP;
  \[                    return LB;
  \]                    return RB;
  ,			return COM;
  :			return COL;
  ;			return SC;
  \.                    return DOT;
  \.\.                  return DOTDOT;

  :=			return ASSIGN;
  =			return EQ;
  "<>"			return NE;
  "<"			return LT;
  "<="			return LE;
  ">"			return GT;
  ">="			return GE;

  \+			return ADD;
  \-			return SUB;
  \*			return MUL;
  \/                    return DIV;
  or			return OR;
  and			return AND;
  xor                   return XOR;
  div			return DIV2;
  mod			return MOD;
  not			return NOT;

  {id}			yylval.symbol = new Symbol(yytext); return ID;

  \n                    line_number++; BEGIN(keyword);
  \{			BEGIN(comment);		/* consume comments */
  {white_space}	        BEGIN(keyword);		/* and white space  */

  .			cout << "Unrecognized character: "<< yytext << endl;
}


<comment>{
  [^\{\}\n]+			                 /* inside comment */
  \{			cout << "comment error" << endl; /* syntax error */
  \}			BEGIN(keyword);		 /* end of comment */
  \n			line_number++;
}


%%

/* End of rules */

/* Additional C code */










