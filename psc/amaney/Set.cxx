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

//template Set<Symbol>;

template<class T> void Set<T>::append(Set<T>& A) {
  Set<T> tmp;
  set_union(begin(), end(), A.begin(), A.end(),
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
