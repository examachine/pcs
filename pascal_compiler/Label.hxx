/*
** Interface file for Label class
**
** eXa/aNaLoG
**
*/

#ifndef Label_h
#define Label_h 1

#include "Symbol.hxx"

// Label is simple
// all it does is adding a prefix to the label number
class Label : public Symbol
{
public:
  Label(Integer l) : Symbol( String('*') + String(Itoa(l)) ) {}
};

#endif









