/*
** Implementation file for main module
**
** front end to compiler
**
** eXa/aNaLoG
**
*/

#include "General.hxx"
#include <iostream.h>
#include <fstream.h>

#include "main.hxx"
#include "pascal_subset.hxx"

main(int argc, char* argv[])
{
  char *source_filename = argv[1];
  cout << "Compiling source file " << source_filename << endl; 
  yyin = fopen(source_filename, "r");
  // yydebug = 1;
  yyparse();
  cout << endl << line_number << " lines counted." << endl;
}
