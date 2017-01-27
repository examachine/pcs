/*
** Interface file for Gen class
**
** eXa/aNaLoG
**
*/

#ifndef Gen_h
#define Gen_h 1

#include <iostream.h>
#include <iomanip.h>

#include "List.hxx"
class Symbol;

extern char* OpNames[];
extern Symbol *empty_symbol;

class Quadruple
{
public:
  enum Op { move = 0, movef,
	    add, sub, mul, div, addf, subf, mulf, divf,
	    or, and, xor, mod,
	    neg, negf,
	    not,
	    jmp, jeqz, jnez, 
	    eq, ne, lt, le, gt, ge,
	    eqf, nef, ltf, lef, gtf, gef,
	    inttofloat,
	    context, call, param, paramf, ret, retval,
	    label, local, localf };
  Op op;
  Symbol *arg1, *arg2, *dest;
  
  // constructors
  Quadruple() {}
  // ** try default values...
  Quadruple(Op o, Symbol *a1, Symbol *a2, Symbol *d)
    : op(o), arg1(a1), arg2(a2), dest(d) {
      if (arg1==0) arg1 = empty_symbol;
      if (arg2==0) arg2 = empty_symbol;
      if (dest==0) dest = empty_symbol;
    }
  friend ostream& operator <<(ostream& out, Quadruple q);
};

typedef List<Quadruple> QuadList;


// Intermediate Code Generator Class
class Gen
{
  QuadList quad_list;

public:

  Gen() {}

  // generate quadruple
  void add(Quadruple q) {
    quad_list.add_tail(q);
  }

  // join another gen to the end of list
  void cat(Gen& gen) {
    quad_list.add_tail(gen.quad_list);
  }

  // output generated code in somewhat readable form
  void emit(ostream& out);
};

#endif
