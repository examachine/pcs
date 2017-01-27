/*
**
** Interface file for module
**
**
**
** exa
**
*/

#ifndef Set_Interface
#define Set_Interface 1

#include "General.hxx"

// set types
template<class T> class Set : public set<T, less<T> > {
public:
  Set() {}
  void append(Set<T>&);
  void clear();
};
template<class T> ostream& operator<<(ostream& o, Set<T>& s);

template<class T> int operator==(const Set<T>&, const Set<T>&);

#endif
