/*
** Implementation file for Constant class
**
** eXa/aNaLoG
**
*/

#include "General.hxx"
#include "Constant.hxx"

// Construct an integer constant
Constant::Constant(Integer c, int v)
{
  name = String('!') + String(Itoa(c));
  type = new IntegerType;
  value.integer = v;
}

// Construct a real constant
Constant::Constant(Integer c, double v)
//: TypedSymbol( String('!') + String(Itoa(c)) , new RealType) 
{
  name = String('!') + String(Itoa(c));
  type = new RealType;
  value.real = v;
}

// Construct a typed constant
Constant::Constant(Integer c, Type *t, void* v)
: TypedSymbol( String('!') + String(Itoa(c)) , t)
{
  int length = type->storage();
  void *val = value.ptr = (void *) new char[length];
  for (int i=0; i<length; i++, val++, v++)
    *(char *)val = *(char *)v;
}

// Construct an integer constant
Constant::Constant(String n, int v)
{
  name = n;
  type = new IntegerType;
  value.integer = v;
}

// Construct a real constant
Constant::Constant(String n, double v)
{
  name = n;
  type = new RealType;
  value.real = v;
}

// Construct a typed constant
Constant::Constant(String n, Type *t, void* v)
{
  name = n;
  type = t;
  int length = type->storage();
  void *val = value.ptr = (void *) new char[length];
  for (int i=0; i<length; i++, val++, v++)
    *(char *)val = *(char *)v;
}


Constant::~Constant() {
}

char* sbuffer=new char[100];
String s;

#include <stdio.h>
// String representation of a constant
String& Constant::str() {

  if (is_integer()) return (s=String(Itoa(Integer(value.integer))));

  if (is_real()) {
    snprintf(sbuffer, 100, "%g", value.real);
    return (s=String(sbuffer));
  }

  // construct hexadecimal representation of data on byte basis
  void *val=value.ptr;
  s = "0x";
  for (int i = 0; i < type->storage(); i++, val++) {
    char c = *((char*)val)+'00';
    s += String(c);
  }
  return s;
}







