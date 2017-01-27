/*
** Implementation file for Gen module
**
** eXa/aNaLoG
**
*/

#include "General.hxx"
#include "Gen.hxx"
#include "Symbol.hxx"
#include "Constant.hxx"

char* OpNames[] =
{ "move", "movef",
  "add", "sub", "mul", "div", "addf", "subf", "mulf", "divf",
  "or", "and", "xor", "mod",
  "neg", "negf",
  "not",
  "jmp", "jeqz", "jnez",
  "seq", "sne", "slt", "sle", "sgt", "sge",
  "seqf", "snef", "sltf", "slef", "sgtf", "sgef",
  "inttofloat",
  "context", "call", "param", "paramf", "ret", "retval",
  "label", "local", "localf" };

Symbol empty_symbol_data("null");
Symbol *empty_symbol = &empty_symbol_data;

// For human readable quadruples
ostream& operator <<(ostream& out, Quadruple q)
{
  // handle context, labels and locals seperately
  if (q.op==Quadruple::context) {
    out << "CONTEXT " << q.dest->str() << endl;
    return out;
  }
  if (q.op==Quadruple::label) {
    out << q.dest->str() << ":" << endl;
    return out;
  }
  if ((q.op==Quadruple::local) || (q.op==Quadruple::localf)) {
    int i = ( dynamic_cast<Constant*>(q.arg1) ) -> value.integer;
    out << "\t." << OpNames[(int)q.op] << " "
      << q.dest->str() << ", " << i << endl;
    return out;
  }
  out << "\t" << OpNames[(int)q.op] << " (";
  out << q.arg1->str() << ", ";
  out << q.arg2->str() << ", ";
  out << q.dest->str() << ")" << endl;
  return out;
}

// output generated code
void Gen::emit(ostream& out)
{
  for (ListTraversal<Quadruple> i = quad_list.beg_head();
       i.state(); i.succ())
    out << quad_list[i];
}
