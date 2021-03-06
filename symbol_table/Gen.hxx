/*
** Interface file for intermediate code generator
**
** eXa/aNaLoG
**
*/

#ifndef INTCODEGEN_H
#define INTCODEGEN_H 1

#include "General.hxx"

#include <iostream.h>
#include <iomanip.h>

#include "List.hxx"
#include "Symbol.hxx"

extern char* OpNames[];

enum Op {move = 0, add, sub, mul, div, neg, or, and, xor,
	 jmp, jeq, jne, jlt, jle, jgt, jge,
	 call, param, label};

extern Symbol *empty_symbol;

class Quadruple
{
public:
  Op op;
  Symbol *arg1, *arg2, *dest;
  
  // constructors
  Quadruple() {}
  Quadruple(Op o, Symbol *a1, Symbol *a2, Symbol *d)
    : op(o), arg1(a1), arg2(a2), dest(d) {
      if (arg1==0) arg1 = empty_symbol;
      if (arg2==0) arg2 = empty_symbol;
      if (dest==0) dest = empty_symbol;
    }
  friend ostream& operator <<(ostream& out, Quadruple q);
};

inline ostream& operator <<(ostream& out, Quadruple q) {
  // handle labels seperately
  out << "\t" << OpNames[(int)q.op] << "(";
  out << q.arg1->str() << ",";
  out << q.arg2->str() << ",";
  out << q.dest->str() << ")" << endl;
}

typedef List<Quadruple> QuadList;

// Intermediate Code Generator Class
class Gen
{
  QuadList quad_list;

public:

  Gen() {}

  // generate quadruple
  add(Quadruple q) {
    quad_list.add_tail(q);
  }

  // join another gen to the end of list
  cat(Gen& gen) {
    quad_list.add_tail(gen.quad_list);
  }

  // output generated code
  emit(ostream& out) {
    for (ListTraversal<Quadruple> i = quad_list.beg_head();
	 i.state(); i.succ())
      out << quad_list[i];
  }
};

#endif
