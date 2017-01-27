/*
** Interface file for symbol class
**
** eXa/aNaLoG
**
*/

#ifndef SYMBOL_H
#define SYMBOL_H 1

#include <String.h>
#include <SLList.h>

// A symbol refers to the name of an entity
// Base class for all symbols
class Symbol
{
public:
  String name;

  Symbol() {}
  Symbol(String n) : name(n) {}
  virtual ~Symbol() {}		// polymorphic or burst!
  virtual String& str() { return name; }
};

// list of symbols
typedef SLList<Symbol*> SymbolList;


// Label is simple
class Label : public Symbol
{
public:
  Label() {}
};


// abstract base class for type
class Type
{
public:
  Type()  {}
  virtual int storage() = 0;	// storage requirement of type
};

// single linked list of pointers to Type
typedef SLList<Type*> TypeList; // we need a list of types

class Void : public Type
{
  Void() {}
  int storage() { return 0; }	// no storage
};  

class Integer : public Type
{
public:
  Integer() {}
  int storage() { return 4; }
};

class Real : public Type
{
public:
  Real() {}
  int storage() { return 8; }
};


// Variable has name, type, address attributes
class Variable : public Symbol
{
public:
  Type *type;
  int offset; 

  Variable(String n, Type *t, int o) : Symbol(n), type(t), offset(o) {}
  virtual ~Variable() {}
};


// A Constant is a Variable whose value is statically bound
class Constant : public Variable
{
public:
  void *value;
  String s;

  Constant(String n, Type *t, int o, void* v)
    : Variable(n, t, o), value(v) {}
  ~Constant() { delete value; }
  String& str() {
    void *val=value;
    s = "0x";
    for (int i = 0; i < type->storage(); i++, val++) {
      char c = *((char*)val) + '0';
      s += String(c);
    }
    return s;
  }
};

#endif



