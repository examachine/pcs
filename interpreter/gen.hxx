/*
** Interface file for intermediate code generator
**
** eXa/aNaLoG
**
*/

#ifndef INTCODEGEN_H
#define INTCODEGEN_H 1

#include <iostream.h>
#include <iomanip.h>
#include <DLList.h>

char* OpNames[] =
{ "move", "add", "sub", "mul", "div", "neg", "or", "and", "xor",
  "jmp", "jeq", "jne", "jlt", "jle", "jgt", "jge",
  "call", "param", "label" };

enum Op {move = 0, add, sub, mul, div, neg, or, and, xor,
	 jmp, jeq, jne, jlt, jle, jgt, jge,
	 call, param, label};

class Quadruple
{
public:
  Op op;
  Symbol* arg1, arg2, dest;

  Quadruple() {}
  friend ostream& operator <<(ostream& out, Quadruple q);
};

inline ostream& operator <<(ostream& out, Quadruple q) {
  out << "\t" << OpNames[(int)q.op] << "(";
  q.arg1->str(out);
  q.arg2->str(out);
  q.dest->str(out);
  out << ")" << endl;
}

typedef DLList<Quadruple> QuadList;

// Intermediate Code Generator Class
class Gen
{
  ostream& out;
  QuadList quad_list;

  g3(char *op, int s1, int s2, int d)
    { out << "\t" << op << "\t" << s1 << "," << s2 << "," << d << endl; }
  g2(char *op, int s, int d) 
    { out << "\t" << op << "\t" << s1 << "," << d << endl; }
  g1(char *op, int s) 
    { out << "\t" << op << "\t" << s << endl; }

public:

  Gen(ostream& o) : out(o){}

  // join another gen to the end of list
  cat(Gen gen&) {
    quad_list.join(gen);
  }

  // output generated code
  emit() {
    for (Pix i = quad_list.first(); i; quad_list.next(i))
      out << quad_list(i);
  }
};

#endif









