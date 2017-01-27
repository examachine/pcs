/*
** Interface file for context module
**
**
**
** eXa/aNaLoG
**
*/

#ifndef CONTEXT_H
#define CONTEXT_H 1

#include "General.hxx"
#include "Symbol.hxx"
#include "Type.hxx"
#include "Variable.hxx"
#include "SymbolTable.hxx"

// Base class for contexts
// symbol table access
class Context : public Symbol
{
public:

  // symbol table
  SymbolTable symbol_table;

  // relative address
  int offset;

  Context() {}
  virtual ~Context() {}
  declare_variables(SymbolList&, Type*);
  declare_procedure(String& name, TypeList& arguments);
  declare_function(String& name, TypeList& arguments, Type* return_type);
};

class Function : public Context
{
public:
  TypeList formal_parameters;
  Type return_type;

  Function() {}
};

#endif









