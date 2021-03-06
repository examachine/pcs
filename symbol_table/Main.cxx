/*
** Implementation file for module
**
** eXa/aNaLoG
**
*/

#include "General.hxx"
#include "SymbolTable.hxx"
#include "Type.hxx"
#include "Variable.hxx"
main()
{

  SymbolTable a;

  // do something with it

  if (a.table.empty) cout << "empty now" << endl;

  Variable *v1 = new Variable("Var1", new Integer, 10);
  Symbol *symbol = new Symbol("a symbol");


  a.insert(v1);
  a.insert(symbol);

  a.del("a symbol");

  cout << "length: " << a.table.length() << endl;

  Symbol *sym=a.lookup("Var1");
  cout << typeid(*sym).name() << "," << typeid(Variable).name();
  Variable *s=dynamic_cast<Variable *>(sym);
  cout << s << " : " << v1 << endl;
  if (!s)
    cout << "not found";
  else {
    cout << s->name << endl;
    cout << s->offset << endl;
  }

}
