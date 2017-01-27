/*
** Implementation file for NFAe module
**
**
** exa
**
*/

#include "NFAe.hxx"

//int operator<(Transition a, Transition b) { return a.from < b.from; }

template<class T> void myvec<T>::append(myvec<T>& v) {
  iterator i=v.begin(), j=v.end();
  for (; i!=j; i++) {
    if (!find(*i)) {
      push_back(*i);
    }
  }
}

template<class T> int myvec<T>::find(T value) {
  if (empty()) return 0;
  iterator i=begin(), j=end();
  for (; i!=j; i++)
    if (*i==value)
      return 1;
  return 0;
}

template<class T> void myvec<T>::clear() {
  int len = size();
  for (int i=0; i<len; i++) {
    pop_back();
  }
}

template<class T> ostream& operator<<(ostream& out, myvec<T> v ) {
  if (v.empty()) {
    out << "<>";
    return out;
  }
  myvec<T>::iterator i=v.begin(), j=v.end();
  out << '<' << *i++; 
  for (;i!=j;i++)
    out << ", " << *i;
  out << '>';
  return out;
}

void tranmap::list(ostream& out){
  //out << "transitions:\n";
   iterator i=begin(), stop=end();
   for (;i!=stop;i++) {
     map<int,intset, less<int> >::iterator
       i2=(*i).second.begin(), stop2=(*i).second.end();
     for (;i2!=stop2;i2++) {
       intset &a=(*i2).second;
       if (!a.empty()) {
	 out << (*i).first << ' ' << (char)(*i2).first << ' ';
	 intset::iterator i3=a.begin(), stop3=a.end();
	 for (;i3!=stop3;i3++)
	   out << *i3 << ' ';
	 out << endl;
       }
     }
   }
}

// read NFAe from a file name fname
void NFAe::read(const char *fname) {
}

// output NFAe to a stream
ostream& operator<<(ostream& out, NFAe& n) {
  if (n.has_epsilon)
    out << "NFAe" << endl;
  else
    out << "NFA" << endl;
  {
    charset::iterator i=n.alphabet.begin(), end=n.alphabet.end();
    for (;i!=end;i++)
      out << *i;
    out << endl;
  }
  out << n.states << endl;
  {
    intset::iterator i=n.final_states.begin(), end=n.final_states.end();
    for (;i!=end;i++)
      out << *i << ' ';
    out << endl;
  }
  n.transitions.list(out);
}


// epsilon closure of a state q
intset NFAe::e_closure(int q)
{
  intset v;
  return e_closure(q,v);
}

// epsilon closure of a set of states
intset NFAe::e_closure(intset& states)
{
  intset closure;
  intset::iterator b=states.begin(), e=states.end();
  for (intset::iterator i=b; i!=e; i++) {
    closure.append(e_closure(*i));
  }
  return closure;
}

// auxiliary function
// performs a DFS on epsilon edges
intset NFAe::e_closure(int q, intset& visited)
{
   intset closure; closure.insert(q);

   // find all transitions with epsilon
   intset estates = transitions[q][epsilon];
   intset::iterator b=estates.begin(), e=estates.end();

   // and e-closures of those
   visited.insert(q);
   for (intset::iterator i=b; i!=e; i++) {
     // there are no e-cycles really
     // but for the sake of completeness do a true DFS
     if ( !visited.find(*i) ) {
     }
       closure.append(e_closure(*i, visited));
       visited.insert(*i);
   }
   return closure;
}


// destructively convert epsilon transitions to non epsilon transitions
void NFAe::convert_etran()
{
  intset v;

  // path conversion
  convert_etran_aux();

  // if q0 can reach with epsilons to a final state
  intset closure_0 = e_closure(0);
  intset::iterator i=final_states.begin(), j=final_states.end();
  int find_flag = 0;
  for (;(i!=j) && (!find_flag); i++)
    if (closure_0.find(*i))
      find_flag = 1;
  if (find_flag==1) // if found add q0 to the final states
    final_states.insert(0);

  // eliminate epsilon-transitions altogether
  eliminate_epsilons();

  has_epsilon = false;
}

// convert transition table
// adds required non epsilon transitions
// auxiliary function for conversion / core of conversion algorithm
void NFAe::convert_etran_aux()
{
  int q;
  for (q=0; q<states; q++) {
    intset e_reachable = e_closure(q);
    intset::iterator b = e_reachable.begin(), e=e_reachable.end();
    // for each epsilon-reachable state
    for (intset::iterator i=b; i!=e; i++) {
      // check all non epsilon transitions from *i
      charset::iterator x=alphabet.begin(), y=alphabet.end();
      // for each input alphabet symbol *x
      for(;x!=y;x++) {
	// states which are reachable via symbol x from i
	intset non_e = transitions[*i][*x];
	// epsilon-closure of non epsilon transition from *i on symbol *x
	intset target_states = e_closure(non_e);
	// add non epsilon transition from q to target_states on symbol *x
	transitions[q][*x].append(target_states);
      }
    }
  }
}

void NFAe::eliminate_epsilons()
{
  // for each state
  for (int state=0; state < states; state++)
    transitions[state][epsilon].clear(); // empty set
}
