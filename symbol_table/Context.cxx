/*
** Implementation file for context module
**
** eXa/aNaLoG
**
*/

#include "General.hxx"
#include "Context.hxx"

void Context::declare_variables(SymbolList variables, Type type)
{
  for (Pix i=variables.first(); i; variables.next(i)) {
    if (symbol_table.find(variables[i].name)) {
      //"Duplicate declaration of variable" 
    }
    else {
      symbol_table.insert(new Variable(variables[i].name, type, offset));
      offset += type.storage;
    }
  }
}


