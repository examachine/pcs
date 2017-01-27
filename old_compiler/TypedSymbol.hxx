/*
** Interface file for TypedSymbol class
**
** eXa/aNaLoG
**
*/

#ifndef TypedSymbol_h
#define TypedSymbol_h 1

#include "Symbol.hxx"
#include "Type.hxx"

// Symbol associated with a static type
class TypedSymbol : public Symbol
{
protected:
  TypedSymbol() {}
public:
  Type *type;			// simulate multiple polymorphism...

  TypedSymbol(String n, Type *t) : Symbol(n), type(t) {}
  virtual ~TypedSymbol() { /*delete type;*/ }

  int is_integer() {
    return (typeid(*type)==typeid(IntegerType));
  }

  int is_real() {
    return (typeid(*type)==typeid(RealType));
  }

  //int is_array() {
  //  return (typeid(*type)==typeid(ArrayType));
  //}

};

#endif









