/*
** Implementation file for module
**
** eXa/aNaLoG
**
*/

#include "General.hxx"
#include "Gen.hxx"

char* OpNames[] =
{ "move", "add", "sub", "mul", "div", "neg", "or", "and", "xor",
  "jmp", "jeq", "jne", "jlt", "jle", "jgt", "jge",
  "call", "param", "label" };

Symbol empty_symbol_data("null");
Symbol *empty_symbol = &empty_symbol_data;
