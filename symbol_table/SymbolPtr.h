/*
**
** eXa/aNaLoG
**
*/

#ifndef SYMBOLPTR_H
#define SYMBOLPTR_H 1

#include "General.hxx"
#include "Symbol.hxx"

// Symbol table requires use of pointer types
typedef Symbol *SymbolPtr;

// comparison : less-than -> < 0; equal -> 0; greater-than -> > 0
#define SymbolPtrCMP(a, b) ( compare(a->name, b->name) )

// hash function
#include <builtin.h>
#define SymbolPtrHASH(x)  (hashpjw((const char *)x->name))
#define DEFAULT_INITIAL_CAPACITY 211

#endif









