/*
** Interface file for module
** eXa/aNaLoG
**
*/

#ifndef STRINGPTR_H
#define STRINGPTR_H 1

#include "General.hxx"
#include "SymbolPtr.h"

typedef String *StringPtr;

// equality operator
#define StringPtrEQ(a, b)  ((*a) == (*b))

// comparison : less-than -> < 0; equal -> 0; greater-than -> > 0
#define StringPtrCMP(a, b) ( compare(*a, *b) )

// hash function
#include <builtin.h>
#define StringPtrHASH(x)  (hashpjw((const char *)(*x)))
#define DEFAULT_INITIAL_CAPACITY 211

#endif
