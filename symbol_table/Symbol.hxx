/*
** Interface file for symbol class
**
** eXa/aNaLoG
**
*/

#ifndef SYMBOL_H
#define SYMBOL_H 1

#include <String.h>
#include <SLList.h>

class SymbolPtrVHSet;
// A symbol refers to the name of an entity
// Base class for all symbols
class Symbol
{
public:
  String name;

  Symbol() {}
  Symbol(String n) : name(n) {}
  virtual ~Symbol() {}		// polymorphic or burst!
  virtual String& str() { return name; }
};

// list of symbols
typedef SLList<Symbol*> SymbolList;

#endif
