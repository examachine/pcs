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

void main()
{
  Gen a;
  a.add(Quadruple(add,0,0,0));
  a.add(Quadruple(and,0,0,0));

  Gen g;
  g.add(Quadruple(label,0,0,0));
  g.add(Quadruple(xor,0,0,0));
  g.cat(a);
  g.emit(cout);

}
