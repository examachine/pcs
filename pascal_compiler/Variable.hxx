/*
** Interface file for Variable class
**
** eXa/aNaLoG
**
*/


#ifndef Variable_h
#define Variable_h 1

#include "TypedSymbol.hxx"

// Variable has name, type, address attributes
class Variable : virtual public TypedSymbol
{
protected:
  Variable() {}
public:
  int offset; 

  Variable(String n, Type *t, int o)
    //: TypedSymbol(n, t), offset(o) {} // g++ bug
    {
      name = n;
      type = t;
      offset = o;
    }

  virtual ~Variable() {}

};


#endif












