/*
** Interface file for Constant class
**
** eXa/aNaLoG
**
*/

#ifndef Constant_h
#define Constant_h 1

#include "TypedSymbol.hxx"

// A Constant is a Symbol whose value is statically bound
// and contaminates no run-time storage at all
class Constant : virtual public TypedSymbol
{
protected:
  Constant() {}
public:
  union {
    int integer;
    double real;
    void *ptr;
  } value;

  Constant(Integer c, int v);
  Constant(Integer c, double v);
  Constant(Integer c, Type *t, void* v);

  Constant(String n, int v);
  Constant(String n, double v);
  Constant(String n, Type *t, void *v);

  virtual ~Constant();

  String s;
  String& str();

};

#endif















