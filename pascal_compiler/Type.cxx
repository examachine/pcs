/*
** Implementation file for Type class
**
** eXa/aNaLoG
*/

#include "General.hxx"
#include "Type.hxx"
#include "Gen.hxx"
#include "Variable.hxx"
#include "Constant.hxx"

void IntegerType::declare_local(Gen* g, Variable* v) {
  Symbol *s1=new Constant(Integer(0), (int)1);
  g->add(Quadruple(Quadruple::local, s1, (Symbol*)0, (Symbol*)v));
}

void RealType::declare_local(Gen* g, Variable* v) {
  Symbol *s1=new Constant(Integer(0), (int)1);
  g->add(Quadruple(Quadruple::localf, s1, (Symbol*)0, (Symbol*)v));
}


