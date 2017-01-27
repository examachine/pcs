/*
** Lexical analyzer for compiler
**
** Flex source
**
** exa/analog
**
*/


%{
#include <stdio.h>
int line_number = 1;
%}

/* Options */

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

/* Rules */

%%

ebe		/* boo  */
eben		printf("shit\n");

%%

/* End of rules */

/* Additional C code */

void main() {
	yylex();
}








