/*
** Interface file for Expression class
**
** eXa/aNaLoG
**
*/

#ifndef Expression_h
#define Expression_h 1

#include "List.hxx"
#include "Variable.hxx"
#include "Constant.hxx"
#include "Gen.hxx"


// An Expression is a Typed Symbol capable of code generation
class Expression : virtual public TypedSymbol
{
protected:

  Expression() {}

  String get_name(Integer n) {
    return String('$') + String(Itoa(n));
  }

  String get_name(String s) {
    return String('$') + s;
  }

public:

  Gen gen;

  Expression(Integer n, Type *t)
    : TypedSymbol( get_name(n), t) {}

  virtual ~Expression() {}

};

typedef List<Expression*> ExprList; // we need a list of expressions
typedef ListTraversal<Expression*> ExprTrav;


class VariableExpression : public Expression, public Variable
{
public:

  VariableExpression(Integer n, Type *t, int o)
    : Variable(get_name(n), t, o) {}

  VariableExpression(Variable *v)
    : Variable(get_name(v->name), v->type, v->offset) {}
};


class ConstantExpression : public Expression, public Constant
{
public:

  ConstantExpression(Integer n, int v)
    : Constant(n, v) { }

  ConstantExpression(Integer n, double v)
    : Constant(n, v) { }

  ConstantExpression(Integer n, Type *t, void *v)
    : Constant(n, t, v) { }

  ConstantExpression(Integer n, Constant *c)
    : Expression(n, c->type) {value=c->value;}
};

#endif








