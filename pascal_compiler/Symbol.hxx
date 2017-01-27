/*
** Interface file for Symbol class
**
** eXa/aNaLoG
**
*/

#ifndef Symbol_h
#define Symbol_h 1

#include <String.h>
#include "List.hxx"

// A symbol refers to the name of an entity
// Base class for all symbols
class Symbol
{
public:
  String name;

  Symbol() {}			// SymbolTable requires this
  Symbol(String n) : name(n) {}
  virtual ~Symbol() {}		// polymorphic or burst!
  virtual String& str() { return name; }
};

// list of symbols
typedef List<Symbol*> SymbolList;
typedef ListTraversal<Symbol*> SymbolTrav;

#endif











