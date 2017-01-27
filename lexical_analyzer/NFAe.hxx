/*
** Interface file for NFAe module
**
**
** exa
*/

#ifndef NFAe_h
#define NFAe_h 1

#include "General.hxx"

#define epsilon 'e'

// set types
template<class T> class myvec : public vector<T> {
public:
  void append(myvec<T>&);
  int find(T);
  void insert(T a) {
    if (!find(a))
      push_back(a);
  }
  void clear();
};

template<class T> ostream& operator<<(ostream& o, myvec<T> v );

typedef myvec<int> intset;
typedef myvec<char> charset;

typedef map<int, intset, less<int> > symstatesmap;
class tranmap : public map<int, map<int, intset, less<int> >, less<int> > {
public:
  void list(ostream&);
};

// non-deterministic finite automata with/without e-transitions
class NFAe {
public:
  NFAe(int e) : has_epsilon(e) {}
  int has_epsilon;
  int states;
  charset alphabet;
  tranmap transitions;
  intset final_states;
  void read(const char*);
  friend ostream& operator<<(ostream& out, NFAe& n);

  intset e_closure(int);
  intset e_closure(intset&);
  void convert_etran();
  void eliminate_epsilons();
private:
  intset e_closure(int q, intset&);
  void convert_etran_aux();
};

#endif









