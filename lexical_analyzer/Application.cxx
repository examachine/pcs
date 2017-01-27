/*
** C++ source for Application
**
** exa
**
*/

#include "General.hxx"
#include "Scanner.hxx"

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

  // Scanner for given file
  Scanner scanner(argv[1]);
  ostream *out;
  if (argc==3)
    out = new ofstream(argv[2]);
  else
    out = &cout;

  while (!scanner.finished())
    scanner.print_next_token(*out);
}

