/*
** Implementation file for Type class
**
** eXa/aNaLoG
*/

#include "General.hxx"
#include "Type.hxx"
#include "Gen.hxx"
#include "Variable.hxx"

inline void Integer::declare_local(Gen& g, Variable* v) {
  Symbol *s1=new Constant(1);
  g.add(Quadruple(Quadruple::local, s1, (Symbol*)0, (Symbol*)v));
}

inline void Real::declare_local(Gen& g, Variable* v) {
  Symbol *s1=new Constant(1);
  g.add(Quadruple(Quadruple::localf, s1, (Symbol*)0, (Symbol*)v));
}


