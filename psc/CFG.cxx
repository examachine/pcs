/*
**
** Implementation file for module
**
**
**
** exa
**
*/

#include "PSCInterface.hxx"

//template Set<MetaSymbol>;

// *********** g++ bug ***************
//const Symbol Symbol::Epsilon = "e"; // "\x01";

const Symbol epsilon = "epsilon";
int CFG::counter = 0;

template<class T> void Set<T>::append(Set<T>& A) {
  Set<T> tmp;
  set_union(begin(), end(), A.begin(), A.end(),
            insert_iterator< Set<T> >(tmp, tmp.begin()) );
  *this = tmp;
}

template<class T> void Set<T>::subtract(Set<T>& A) {
  Set<T> tmp;
  set_difference(begin(), end(), A.begin(), A.end(),
            insert_iterator< Set<T> >(tmp, tmp.begin()) );
  *this = tmp;
}

template<class T> void Set<T>::clear() {
  erase(begin(), end());
}

template<class T> ostream& operator<<(ostream& out, Set<T>& v ) {
  if (v.empty()) {
    out << "{}";
    return out;
  }
  Set<T>::iterator i=v.begin(), j=v.end();
  out << '{' << *i++; 
  for (;i!=j;i++)
    out << ", " << *i;
  out << '}';
  //for (;i!=j;i++)
  //  out << *i;
  return out;
}

template<class T> int operator==(const Set<T>& lhs, const Set<T>& rhs) {
  return (set<T, less<T> >)lhs == (set<T, less<T> >)rhs;
}

// CFG
void CFG::init()
{
  PSp::init_class();
  PS::init_class();
  PC::init_class();
  // g++ bug >>>Program::init_class;<<< accepts and compiles!!!!
 
  V["Sp"] = &PSp::Representative;
  V["S"] = &PS::Representative; 
  V["C"] = &PC::Representative;
  T["keyword"] = &Pkeyword::Representative; 
  T["id"] = &Pid::Representative;
  T["intnum"] = &Pintnum::Representative;
  T["realnum"] = &Prealnum::Representative;
  T["relop"] = &Prelop::Representative;
  T["adop"] = &Paddop::Representative;
  T["multop"] = &Pmultop::Representative;
  T["assigop"] = &Passigop::Representative;
  T["delimiter"] = &Pdelimiter::Representative;
  T["eof"] = &Peof::Representative;
  S = "Sp";
  eof_symbol = "eof"; // Mandatory!
  cout << to_string();
  //cout << "First: " << FIRST("Sp") << endl;
  items();
}

Set<MetaSymbol> CFG::FIRST(MetaSymbol X)
{
  Set<MetaSymbol> first;
    first.clear();
  if (X==epsilon) {
    //cout << "epsilon" << endl;
    first.insert(X);		// alone, or  --> X
  }
  else if (T.find(X) != T.end()) { //a terminal
    //cout << " is terminal" << endl;
    first.insert(X);
  }
  else if (V.find(X) != V.end()) { //a variable
    //cout << " is variable" << endl;
    list<GProduction> prods = V[X]->get_prods();
    list<GProduction>::iterator a = prods.begin(), b = prods.end();
    for (; a!=b; a++) {
      vector<MetaSymbol> & rhs = a->rhs;
      first.append(sFIRST(a->lhs, a->rhs));
    }
  }
  else {
    cout << "MetaSymbol not found " << endl;
    exit(0);
  }
  return first;
}

Set<MetaSymbol> CFG::sFIRST(MetaSymbol lhs, vector<MetaSymbol>& rhs)
{
  Set<MetaSymbol> first;
  vector<MetaSymbol>::iterator c = rhs.begin(), d = rhs.end();
  Set<MetaSymbol> syms;//, newsyms;
  if (c!=d) {
    bool flag = true;
	if (*c == lhs) flag = false;
	if (flag) {
	  //cout << X << "--> " << *c;
	  syms = FIRST(*(c++));
	  first.append(syms);
	}
	while ((c!=d) && flag) {
	  if (*c == lhs) flag = false;
	  // if epsilon is not in the previous
	  if (syms.find(epsilon)==syms.end())
	    flag = false;
	  if (flag) {
	    syms = FIRST(*(c++));
	    // remove epsilon
	    first.erase(epsilon);
	    first.append(syms);
	  }
	}
  }
  else {
    cout << "Empty right hand side!" << endl;
  }

  return first;
}


// Closure of a set of LR(1) Items
Items CFG::closure(Items I)
{
  // entry
  if (!I.empty()) {
    //cout << ">>>entry\n" << I << endl;
    Items new_items;
    // for each item in I
    Items::iterator i0 = I.begin(), j0 = I.end();
    for (; i0!=j0; i0++) {
      Item& item = *i0; 
      // for all [A --> alpha . B beta , a] in I
      GProduction & Ap = *item.prod;
      if (item.dot>=Ap.rhs.size()) continue; // get back if dot at rightmost
      MetaSymbol B = Ap.rhs[item.dot];
      if (V.find(B) == V.end())
	continue;
      //cout << "checking " << item << "****************" << endl;
      // all productions of the form B --> gamma
      list<GProduction>& Bprods = V[B]->get_prods();
      // for each B --> gamma
      list<GProduction>::iterator i1 = Bprods.begin(), j1 = Bprods.end();
      for (; i1!=j1; i1++) {
	GProduction& Bproduction = *i1;
	vector<MetaSymbol> & gamma = Bproduction.rhs;
	vector<MetaSymbol> follow;
	copy(Ap.rhs.begin() + item.dot + 1, Ap.rhs.end(),
	     insert_iterator< vector<MetaSymbol> >(follow, follow.begin()) );
	follow.push_back(item.lookahead);
	//cout << Bproduction.to_string() << endl;
	//vector<MetaSymbol>::iterator i3 = follow.begin(), j3 = follow.end();
	//for (; i3!=j3; i3++)
	//  cout << " : " << *i3;
	//cout << endl;
	// FIRST(beta a)
	Set<MetaSymbol> first = sFIRST("", follow);
	Set<MetaSymbol>::iterator i2 = first.begin(), j2 = first.end();
	for (; i2!=j2; i2++) {
	  Item firstitem;
	  firstitem.prod = &Bproduction;
	  firstitem.dot = 0;
	  firstitem.lookahead = *i2;
	  //cout << "inserting " << firstitem << endl;
	  //if (I.find(firstitem)==I.end())
	  new_items.insert(firstitem);
	}
      }
    }
    I.append(closure(new_items));
  }
  //cout << "<<<exit\n" << I << endl ;
  return I;
}

// The goto function for a set of LR(1) Items of grammar symbol X
Items CFG::go(Items I, MetaSymbol X)
{
  Items J;
  Items::iterator i0 = I.begin(), j0 = I.end();
  for (; i0!=j0; i0++) {
    Item& item = *i0;
    GProduction& prod = *item.prod;
    //cout << item;
    if (item.dot>=prod.rhs.size()) continue; // get back if dot at rightmost
    MetaSymbol sym = prod.rhs[item.dot];
    if (sym==X /*&& V.find(sym) != V.end()*/) {
      item.dot++;
      //cout << "put " << item;
      J.insert(item);
    }
  }
  //cout << "closure of " << J;
  //Items Z = closure(J);
  //cout << Z;
  //return Z;
  return closure(J);
}

void CFG::items()
{
  Items I;
  Item first;
  list<GProduction>::iterator prod = V["Sp"]->get_prods().begin();
  first.prod = &(*prod);
  first.dot = 0;
  first.lookahead = "eof";
  I.insert(first);
  reset_uid_gen();
  I.index = gen_uid();
  C.insert(closure(I));
  C = items_aux(C);
  // enumerate Sets of Items
  Set<Items>::iterator i0 = C.begin(), j0 = C.end();
  for (int i=0; i0!=j0; i0++, i++) {
    //i0->index = i;
    cout << i0->index << ":";
  }
  cout << "Canonical collection of LR(1) items is " << endl;
  cout << "---------------------------------------" << endl;
  cout << C << endl;
  construct_parsing_tables();
  print_parsing_tables();
}

Set<Items> CFG::items_aux(Set<Items> sets)
{
  Set<Items> gnu_set;
  Set<Items>::iterator i0 = sets.begin(), j0 = sets.end();
  for (; i0!=j0; i0++) {
    Items& I = *i0;
    // For all variable symbols X
    GVariables::iterator i1 = V.begin(), j1 = V.end();
    for (; i1!=j1;i1++) {
      MetaSymbol X = i1->first;
      Items Xp = go(I, X);
      if (!Xp.empty()) {
	Xp.index = gen_uid();
	gnu_set.insert(Xp);
	// memoize go;
	go_table[I.index][X] = Xp.index;
      }
    }
    // And for all Terminal symbols X
    GTerminals::iterator i2 = T.begin(), j2 = T.end();
    for (; i2!=j2; i2++) {
      MetaSymbol X = i2->first;
      Items Xp = go(I, X);
      //cout << "Items from Terminals " << Xp << endl; 
      if (!Xp.empty()) {
	Xp.index = gen_uid();
	gnu_set.insert(Xp);
	// memoize go
	go_table[I.index][X] = Xp.index;
      }
    }
  }
  //cout <<  "Sets of items initially" << sets << endl;
  gnu_set.subtract(sets);
  //cout <<  "new Sets of items " << gnu_set << endl;
  if (!gnu_set.empty()) {
    //Set<Items> t;
    //t = items_aux(gnu_set);
    //sets.append(t);
    //cout << "after union stuff" << sets << endl;
    sets.append(items_aux(gnu_set));
  }
  return sets;
}

void CFG::construct_parsing_tables()
{
  Action new_action;
  // for each set of items I in C
  Set<Items>::iterator i0 = C.begin(), j0 = C.end();
  for (; i0!=j0; i0++) {
    Items & I = *i0;
    Items::iterator i1 = I.begin(), j1 = I.end();
    for (;i1!=j1; i1++) {
      Item & item = *i1;
      GProduction & prod = *item.prod;
      // shift action
      // [A --> alpha . a beta, b] a nonterminal
      if (item.dot<prod.rhs.size()) {
	MetaSymbol a = prod.rhs[item.dot];
	if ((T.find(a)!=T.end()) &&
	    (go_table[I.index].find(a) != go_table[I.index].end())) {
	  new_action.type = Action::shift;
	  new_action.operand.state = go_table[I.index][a];
	  action_table[I.index][a] = new_action;
	}
      }
      else { // then the dot is at the end
	if ((prod.lhs == S) && (item.lookahead == eof_symbol)) {
	  new_action.type = Action::accept;
	  action_table[I.index][item.lookahead] = new_action;
	}
	else {
	  new_action.type = Action::reduce;
	  new_action.operand.prod = &prod;
	  action_table[I.index][item.lookahead] = new_action;
	}
      }
    }
  }
}

void CFG::print_parsing_tables()
{
  cout << "\nAction table\n------------\n";
  ActionTable::iterator i2 = action_table.begin(), j2 = action_table.end();
  for (;i2!=j2; i2++) {
    map<MetaSymbol, Action> & tmp = i2->second;
    map<MetaSymbol, Action>::iterator i3 = tmp.begin(), j3 = tmp.end();
    for (;i3!=j3; i3++) {
      cout << "action(" << i2->first << "," << 
	i3->first << ") = ";
      if (i3->second.type == Action::shift)
	cout << "shift " << i3->second.operand.state << endl;
      else if (i3->second.type == Action::reduce)
	cout << "reduce " << i3->second.operand.prod->to_string() << endl;
      else if (i3->second.type == Action::accept)
	cout << "accept " << endl;
      else if (i3->second.type == Action::error)
	cout << "error " << endl;
    }
  }
  cout << "\nGo table\n--------\n";
  GoTable::iterator i0 = go_table.begin(), j0 = go_table.end();
  for (;i0!=j0; i0++) {
    map<MetaSymbol, int> & tmp = i0->second;
    map<MetaSymbol, int>::iterator i1 = tmp.begin(), j1 = tmp.end();
    for (;i1!=j1; i1++)
      cout << "go(" << i0->first << "," << 
	i1->first << ") = " << i1->second << endl;
  }
}

void CFG::parse(char *source_fn, ostream& out)
{
  cout << "\nParsing source file " << source_fn << "\n";
  cout << "Initializing lexical analyzer\n";
  // Scanner for given file
  Scanner scanner(source_fn);
  //while (!scanner.finished())
  //  scanner.print_next_token(out);
  stack<GSymbol*> p_stack;
  Peof& top_sym = *new Peof;
  top_sym.state = 0; // start state of parser
  p_stack.push(&top_sym);
  GSymbol* terminal; // next terminal
  TokenInfo token;
  token = scanner.scan();
  terminal = T[Scanner::token_names[token.token]]->gen_symbol();
  do {
    int state = p_stack.top()->state;
    Action act =  action_table[state][terminal->get_ms()];
    if (act.type == Action::shift) {
      cerr << "Shifting token " << terminal->get_ms()
	   << " state " << act.operand.state << endl;
      terminal->state = act.operand.state;
      p_stack.push(terminal);
      token = scanner.scan();
      //terminal = gen_symbol(Scanner::token_names[token.token]);
      terminal = T[Scanner::token_names[token.token]]->gen_symbol();
    }
    else if (act.type == Action::reduce) {
      GProduction& prod = *act.operand.prod;
      cerr << "Reducing " << prod.to_string() << endl;
      for (int i = 0; i<prod.rhs.size(); i++) {
	/*delete */p_stack.pop();
      }
      int state2 = p_stack.top()->state;
      GSymbol* A = V[prod.lhs]->gen_symbol();
      A->state = go_table[state2][A->get_ms()];
      p_stack.push(A);
    }
    else if (act.type == Action::accept) {
      cerr << "Parsing complete" << endl;
      break;
    }
    else {
      cout << "Parse error at line " << token.linenumber <<
	", column" << token.lineposition << ", lexeme " <<
	token.attributevalue.lexeme << endl;
      break;
    }
  } while (true);
}

string CFG::to_string()
{
  string str = "G = [\n";
  str += "  V = " + V.to_string() + ",\n";
  str += "  T = "+ T.to_string() + ",\n";
  str += "  P = " + V.prods_to_string(); + ",\n";
  /* MetaSymbolSet::iterator a, b;
  a = T.begin(), b = T.end();
  if (a!=b) str += *(a++);
  for (; a!=b; a++)
    str += ", " + *a;
  str += "],\n";*/
  str += "  S = " + S + "\n";
  str += "]\n";
  return str; // ******** omit return and compiles!
}

// GProduction
string GProduction::to_string()
{
  //string &str = *new string;
  string str = lhs + " --> ";
  vector<MetaSymbol>::iterator a = rhs.begin(),
    b = rhs.end();
  for (; a!=b; a++)
    str += *a + " ";
  return str;
}

// GTerminals

string GTerminals::to_string()
{
  string str = "[";
  iterator a = begin(), b = end();
  if (a!=b) str += (a++)->first;
  for (; a!=b; a++)
    str += ", " + a->first;
  str += "]";
  return str;
}

// GTerminal

// Meta Symbol which refers to
template<const MetaSymbol *m>
const MetaSymbol GTerminal<m>::meta_symbol = *m;

// Representative object
template<const MetaSymbol *m>
GTerminal<m> GTerminal<m>::Representative;

// get_ms
template<const MetaSymbol *m>
MetaSymbol GTerminal<m>::get_ms()
{
  return meta_symbol;
}
// gen symbol
template<const MetaSymbol *m>
GSymbol* GTerminal<m>::gen_symbol()
{
  return new Self;
}

// Terminal c
// first instantiate class
template GTerminal<&Terminals::keyword>;

template GTerminal<&Terminals::id>;

template GTerminal<&Terminals::intnum>;
template GTerminal<&Terminals::realnum>;
template GTerminal<&Terminals::relop>;
template GTerminal<&Terminals::addop>;
template GTerminal<&Terminals::multop>;
template GTerminal<&Terminals::assigop>;
template GTerminal<&Terminals::delimiter>;

template GTerminal<&Terminals::eof>;


// GVariable

//template<const MetaSymbol *m>
//GVariable<m>::


template<const MetaSymbol *m>
string GVariable<m>::productions_to_string()
{
  //string &str = *new string;
  string str ;//= "[ \n";
  list<GProduction>::iterator a = productions.begin(),
    b = productions.end();
  for (; a!=b; a++)
    str += "    " + a->to_string() + "\n";
  //str += "]\n";
  return str;
}

// GVariables

string GVariables::to_string()
{
  string str = "[";
  iterator a = begin(), b = end();
  if (a!=b) str += (a++)->first;
  for (; a!=b; a++)
    str += ", " + a->first;
  str += "]";
  return str;
}

string GVariables::prods_to_string()
{
  string str = "  [\n";
  iterator a = begin(), b = end();
  if (a!=b) str += (a++)->second->productions_to_string();
  for (; a!=b; a++)
    str += a->second->productions_to_string();
  str += "  ]\n";
  return str;
}


// template declaration of class variables

// Associated meta symbol
template<const MetaSymbol *m>
const MetaSymbol GVariable<m>::meta_symbol = *m;

// Productions
template<const MetaSymbol *m>
list<GProduction> GVariable<m>::productions;

// Representative object
template<const MetaSymbol *m>
GVariable<m> GVariable<m>::Representative;

// get prods
template<const MetaSymbol *m>
list<GProduction>& GVariable<m>::get_prods()
{
  return productions;
}

// get_ms
template<const MetaSymbol *m>
MetaSymbol GVariable<m>::get_ms()
{
  return meta_symbol;
}
// gen symbol
template<const MetaSymbol *m>
GSymbol* GVariable<m>::gen_symbol()
{
  return new Self;
}

//template<>
//void GVariable<&Variables::>::

// Variable S'
// first instantiate class
template GVariable<&Variables::Sp>;
// specialization
template<>
void GVariable<&Variables::Sp>::init_class()
{
  GProduction& p1 = genGProduction();
  p1.append("S");
}

// Variable S
// first instantiate class
template GVariable<&Variables::S>;
// specialization
template<>
void GVariable<&Variables::S>::init_class()
{
  GProduction& p1 = genGProduction();
  p1.append("C");
  p1.append("C");
}

// Variable C
// first instantiate class
template GVariable<&Variables::C>;
// specialization
template<>
void GVariable<&Variables::C>::init_class()
{
  GProduction& p1 = genGProduction();
  p1.append("keyword");
  p1.append("C");
  GProduction& p2 = genGProduction();
  p2.append("id");
}

// Variable
// first instantiate class
template GVariable<&Variables::expression>;
// specialization
template<>
void GVariable<&Variables::expression>::init_class()
{
  GProduction& p1 = genGProduction();
  p1.append("simple_expression");
  GProduction& p2 = genGProduction();
  p2.append("simple_expression");
  p2.append("relop");
  p2.append("simple_expression");

}


// Variable
// first instantiate class
template GVariable<&Variables::simple_expression>;
// specialization
template<>
void GVariable<&Variables::simple_expression>::init_class()
{
  GProduction& p1 = genGProduction();
  p1.append("term");
  //GProduction& p2 = genGProduction();
  //p2.append("sign");
  //p2.append("term");
  GProduction& p2 = genGProduction();
  p2.append("simple_expression");
  p2.append("addop");
  p2.append("term");
}


// Variable
// first instantiate class
template GVariable<&Variables::term>;
// specialization
template<>
void GVariable<&Variables::term>::init_class()
{
  GProduction& p1 = genGProduction();
  p1.append("factor");
  GProduction& p2 = genGProduction();
  p2.append("term");
  p2.append("mulop");
  p2.append("factor");
  //p1.append("");
}


// Variable
// first instantiate class
template GVariable<&Variables::factor>;
// specialization
template<>
void GVariable<&Variables::factor>::init_class()
{
  GProduction& p1 = genGProduction();
  p1.append("id");
  //GProduction& p2 = genGProduction();
  //p2.append("intnum");
}




