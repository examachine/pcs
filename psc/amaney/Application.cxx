/*
**
** Implementation file for Application
**
**
**
** exa
**
*/

#include "PSCInterface.hxx"

void main(int argc, char *argv[])
{
  if (argc<2) {
    cerr << "Insufficient number of arguments" << endl;
    exit(0);
  }

  if (argc>4) {
    cerr << "Too many arguments" << endl;
    exit(0);
  }

  CFG G;
  G.init();
  ostream *out;
  if (argc==3)
    out = new ofstream(argv[2]);
  else
    out = &cout;

  //G.parse(argv[1], *out);

}
