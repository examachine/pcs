/*
** Interface file for module
**
**
**
** eXa/aNaLoG
**
*/

#ifndef VARIABLE_H
#define VARIABLE_H 1

#include "Symbol.hxx"
#include "Type.hxx"

// Variable has name, type, address attributes
class Variable : public Symbol
{
public:
  Type *type;
  int offset; 

  Variable(String n, Type *t, int o) : Symbol(n), type(t), offset(o) {}
  virtual ~Variable() {}
};

#endif









