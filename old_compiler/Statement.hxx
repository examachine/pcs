/*
** Interface file for Statement class
**
** eXa/aNaLoG
**
*/

#ifndef Statement_h
#define Statement_h 1

#include "List.hxx"
#include "Gen.hxx"

class Label;

class Statement : public Gen
{
public:
  Label *start;
  Label *end;

  Statement() {}
  virtual ~Statement() {}
};

class IfElseStatement : public Statement
{
public:
  Label *if_else;

  IfElseStatement() {}
  virtual ~IfElseStatement() {}
};

#endif









