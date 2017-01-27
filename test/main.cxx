/*
** Implementation file for main module
**
** front end to compiler
**
** eXa/aNaLoG
**
*/

#include "General.hxx"
#include <iostream.h>
#include <fstream.h>

#include "Gen.hxx"

main(int argc, char* argv[])
{
  //Gen a;
  //a.add(Quadruple(add, 0, 0, 0));
  //a.add(Quadruple(xor, 0, 0, 0));
  Gen g;

  g.add(Quadruple(label, 0, 0, 0));
  g.add(Quadruple(move, 0, 0, 0));

  //g.cat(a);
  g.emit(cout);

}
