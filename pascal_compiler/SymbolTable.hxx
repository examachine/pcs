/*
** Interface file for symbol table module
**
** primitive operations
**
** eXa/aNaLoG
**
*/

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H 1

#include "Symbol.hxx"
#include "StringPtr.SymbolPtr.VHMap.h"

typedef StringPtrSymbolPtrVHMap Table;

class SymbolTable
{
public:
  Table table;
  Symbol def;

  SymbolTable() : table(&def){}

  int contains(Symbol *sym) { table.contains(&(sym->name)); }

  Symbol *lookup(String &key) {
    Pix i = table.seek(&key);
    if (!i)
      return NULL;
    else
      return table.contents(i);
  }

  void insert(Symbol *sym) { table[&(sym->name)] = sym; }

  void del(String &key) {
    if (Pix i = table.seek(&key))  {
      Symbol *sym = table.contents(i);
      table.del(&key);
      delete sym;
    }
  }

};

#endif









