/*
** Interface file for ID class
**
** eXa/aNaLoG
**
*/

#ifndef ID_H
#define ID_H 1

#include <String.h>

class ID
{
public:
  ID() {}
  virtual String classID() {}
  //operator ==(String id) { return classID() == id; }
};

#endif









