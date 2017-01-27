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

// base class for Symbols
// Symbols are used to distinguish entities
class Symbol
{
public:
  String name;

  Symbol() {}			// SymbolTable requires this
  Symbol(String n) : name(n) {}
  virtual ~Symbol() {}		// polymorphic or burst!
  virtual String& str() { return name; } // return a string that denotes name
};

// list of symbols
typedef List<Symbol*> SymbolList;
typedef ListTraversal<Symbol*> SymbolTrav;

#endif











