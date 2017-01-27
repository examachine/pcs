/*
** Interface file for Type class
**
** eXa/aNaLoG
**
*/


#ifndef Type_h
#define Type_h 1

#include "List.hxx"
class Gen;
class Variable;

// abstract base class for type
// a type is not a symbol, strange?
class Type
{
public:
  Type() {}
  virtual ~Type() {}

  virtual int storage() = 0;	// storage requirement of type
  virtual void declare_local(Gen*, Variable*) {}
};

// list of pointers to Type
typedef List<Type*> TypeList; // we need a list of types
typedef ListTraversal<Type*> TypeTrav;

class Void : public Type
{
public:
  Void() {}

  int storage() { return 0; }	// no storage
  void declare_local(Gen* g, Variable* v);
};

class IntegerType : public Type
{
public:
  IntegerType() {}

  int storage() { return 4; }
  void declare_local(Gen* g, Variable* v);
};

class RealType : public Type
{
public:
  RealType() {}

  int storage() { return 8; }
  void declare_local(Gen* g, Variable* v);
};


#endif































