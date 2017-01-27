/*
** Interface file for type module
**
** eXa/aNaLoG
**
*/

#ifndef TYPE_H
#define TYPE_H 1

#include <SLList.h>

// abstract base class for type
class Type
{
public:
  Type()  {}
  virtual int storage() = 0;	// storage requirement of type
};

// single linked list of pointers to Type
typedef SLList<Type*> type_list; // we need a list of types

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
 
#endif









