/*
**
** Interface file for CFG module
**
** Classes for defining context-free grammars
**
** exa
**
*/

#ifndef CFG_Interface
#define CFG_Interface 1

#include "General.hxx"

// set type
template<class T> class Set : public set<T, less<T> > {
public:
  Set() {}
  //Set(T s) { insert(s); }
  void append(Set<T>&);
  void subtract(Set<T>&);
  void clear();
};
template<class T> ostream& operator<<(ostream& o, Set<T>& s);

template<class T> int operator==(const Set<T>&, const Set<T>&);

class Scope;
template < class T >
class SymbolTable;

// Symbol object refers to an entity
// Base class for all symbols
class Symbol : public string
{
public:
  Symbol() {}
  Symbol(char* symbol) : string(symbol) {}
  Symbol(string symbol) : string(symbol) {}

private:
};

extern const Symbol epsilon;

typedef int Object;

template < class C = Object >
//typedef map<Symbol, C> SymbolTable;
class SymbolTable : map<Symbol, C>
{
public:
};

// MetaSymbol is a second order symbol
typedef Symbol MetaSymbol;

// Grammar Symbol
class GSymbol
{
public:
  virtual MetaSymbol get_ms() = 0;
  virtual GSymbol* gen_symbol() = 0;
  int state;			// Parser state
};

// Grammar Terminal
class GTerminalBase : public TokenInfo, public GSymbol
{
public:

};

typedef map<MetaSymbol, GTerminalBase*> TermTable;

class GTerminals : public TermTable
{
public:
  // MetaSymbol Table from symbols to representatives

  string to_string();

};

template <const MetaSymbol *_m>
class GTerminal : public GTerminalBase
{
public:

  typedef GTerminal<_m> Self;

  GTerminal() {}

  // class variables
  static const MetaSymbol meta_symbol;
  static Self Representative;
  MetaSymbol get_ms();
  GSymbol* gen_symbol();

};

// Grammar Production
// lhs -> rhs
// lhs : A Variable
// rhs : A string of Grammar SYmbols
class GProduction
{
public:
  // constructors
  GProduction() {}
  GProduction(MetaSymbol _lhs) : lhs(_lhs) {}
  GProduction(MetaSymbol _lhs, vector<MetaSymbol> _rhs)
    : lhs(_lhs), rhs(_rhs) {}

  // Add a new metasymbol to right of production
  void append(MetaSymbol _sym) { rhs.push_back(_sym); }

  // semantic rule
  //void (*semantic_rule)(GVariableBase&, list<GVariableBase&>&);

  string to_string();

  MetaSymbol lhs;
  vector<MetaSymbol> rhs;
};

// Grammar Variable
// A grammar variable is defined by a symbol such as 'S'
// has attributes that are evaluated during syntax directed translation
class GVariableBase : public GSymbol
{
public:
  typedef void (*SemanticRule)(GVariableBase&, list<GVariableBase&>&);
  //static map<int, SemanticRule> jump_table;

  virtual list<GProduction>& get_prods() = 0;
  virtual string productions_to_string() = 0;
};

typedef map<MetaSymbol, GVariableBase*> VarTable;

class GVariables : public VarTable
{
public:
  // MetaSymbol Table from symbols to representatives

  string to_string();
  string prods_to_string();
};


// The template superclass of all variables in the grammar
// a class of grammar symbols with a common non-terminal symbol
template<const MetaSymbol *_m>
class GVariable : public GVariableBase
{
public:

  typedef GVariable<_m> Self;
  
  GVariable() {}

  // class variables
  static const MetaSymbol meta_symbol;

  // Production rules
  static list<GProduction> productions;

  // Augment the grammar with a new production rule
  static void add(GProduction production)
  { productions.push_back(production); }

  // *****************
  static GProduction& genGProduction()
  {
    productions.push_back(GProduction(meta_symbol));
    list<GProduction>::iterator a = productions.end();
    return *(--a);
  } 

  // initialize variable class
  static void init_class();

  static Self Representative;

  //Self& gen();

  list<GProduction>& get_prods();
  string productions_to_string();
  MetaSymbol get_ms();
  GSymbol* gen_symbol();

private:
};


typedef set<Symbol> SymbolSet;
typedef set<MetaSymbol> MetaSymbolSet;

class Item {
public:
  GProduction* prod;
  int dot;
  MetaSymbol lookahead;
};

inline ostream& operator<<(ostream& o, Item& i) {
  o << i.prod->to_string() << " pos: " << i.dot
    << " lookahead: " << i.lookahead << endl;
  return o;
}

inline operator <(Item& lhs, Item& rhs)
{
  //return (((int)lhs.prod<(int)rhs.prod) & (lhs.dot<rhs.dot) &
  //        (lhs.lookahead < rhs.lookahead));
  if (int(lhs.prod) < int(rhs.prod))
    return true;
  else if (lhs.prod == rhs.prod) {
    if (lhs.dot < rhs.dot)
      return true;
    else if (lhs.dot==rhs.dot) {
      return (lhs.lookahead < rhs.lookahead);
    }
    else return false;
  }
  else return false;
}

//inline operator ==(Item& lhs, Item& rhs)
//{
//  return ((lhs.prod==rhs.prod) & (lhs.dot==rhs.dot) &
//          (lhs.lookahead == rhs.lookahead));
//}

//inline bool operator ==(Items& lhs, Items& rhs) {
//  return (lhs.prod==
//}

class Items : public Set<Item>
{
public:
  void set_index(int i) { index = i; }
  int index;
};

inline operator <(Items& lhs, Items& rhs)
{
  return (lhs.index < rhs.index);
}

// A CFG G is defined as G = (V, T, P, S)
// The sets within 4-tuple G are dynamic
class CFG
{
public:

  CFG() {}

  //MetaSymbolSet V;
  GVariables V;
  GTerminals T;
  // P is defined implicitly in V
  MetaSymbol S;		// start symbol
  MetaSymbol eof_symbol;

  // Canonical Sets of LR(1)Items
  Set<Items> C;

  // Parsing Tables action and go
  struct Action {
    Action() : type(error) {}
    enum {error = 0, shift, reduce, accept} type;
    union {
      int state;
      GProduction* prod;
    } operand;
  };
  typedef map<int, map<MetaSymbol, Action> > ActionTable;
  typedef map<int, map<MetaSymbol, int> > GoTable;
  ActionTable action_table;
  GoTable go_table;

  void init();

  string to_string();
  Set<MetaSymbol> FIRST(MetaSymbol);
  Set<MetaSymbol> sFIRST(MetaSymbol, vector<MetaSymbol>&);
  Items closure(Items);
  Items go(Items, MetaSymbol);
  void items();
  Set<Items> items_aux(Set<Items> sets);
  void construct_parsing_tables();
  void print_parsing_tables();
  void parse(char *, ostream&);

private:
  static int counter;
  void reset_uid_gen() { counter = 0; }
  int gen_uid() { return counter++; }
};

#endif




