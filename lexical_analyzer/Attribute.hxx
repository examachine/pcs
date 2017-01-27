/*
** Interface file for Attributemodule
**
**
**
** exa
**
*/

#ifndef Attribute_Interface
#define Attribute_Interface 1

#include "General.hxx"

struct Attribute {
  string lexeme;
};

struct ID :  Attribute {
  ID() {}
  const string& get_name() { return lexeme; }
};

struct IntNum :  Attribute {
  IntNum(const char* s) : value(atoi(s)) {}
  int value;
};

struct RealNum : Attribute {
  RealNum(const char *s) : value(strtod(s, (char **)NULL)) {}
  double value;
};

struct RelOp : Attribute {
  enum Type {eq, ne, lt, le, gt, ge};

  RelOp(){}
  //RelOp(Type t) : type(t) {}

  //Type type;
};

struct AddOp : Attribute {
  enum Type { add, sub, or };

  AddOp() {}
  //AddOp(Type t) : type(t) {}

  //Type type;
};

struct MultOp : Attribute {
  enum Type { times, over, div, k_mod, k_and };

  MultOp() {}
  //MultOp(Type t) : type(t) {}

  //Type type;
};

struct AssigOp : Attribute {
  AssignOp() {}
};

struct Keyword : Attribute {

  Keyword() {}
  //Keyword(Type t) : type(t) {}

  //Type type;
};

struct Delimiter : Attribute {
  enum Type { dot, comma, semicol, col, dotdot, lb, rb, la, ra };

  Delimiter() {}
  Delimiter(Type t) : type(t) {}

  Type type;
};

#endif









