/*
** Interface file for context module
**
**
**
** eXa/aNaLoG
**
*/

#ifndef CONTEXT_H
#define CONTEXT_H 1

#include "General.hxx"
#include "Type.hxx"
#include "Symbol.hxx"
#include "SymbolTable.hxx"
#include "Label.hxx"
#include "Variable.hxx"
#include "Constant.hxx"
#include "Expression.hxx"
#include "Statement.hxx"
#include "Gen.hxx"


// Base class for contexts
// symbol table access
class Context : public Symbol
{
public:

  Context* enclosing;

  // symbol table
  SymbolTable symbol_table;

  // generated code
  Gen gen;

  int depth;			// nesting depth
  int offset;			// next relative address for local storage
  int tmp;			// next temporary to be generated
  int constant;			// next constant to be generated

  // Constructor
  Context(String, Context*, int);
  virtual ~Context() {}

  String qualified_name;	// full name of context

  String& str() { return qualified_name; }

  void generate_intermediate_code(Statement*);
  int get_offset(Type *t);
  int get_tmp(); 
  static Label* get_label();
  void declare_variables(SymbolList&, Type*);
  void declare_procedure(String& name, TypeList& arguments);
  void declare_function(String& name, TypeList& arguments, Type* return_type);
  VariableExpression* get_varexpr(Variable *v);
  ConstantExpression* get_constexpr(int v);
  ConstantExpression* get_constexpr(double v);
  ConstantExpression* get_constexpr(Type *t, void *v);
  ConstantExpression* get_constexpr(Constant *c);
  Variable* variable_ref(Symbol*);
  Variable* array_ref(Symbol*, int);
  Statement* assign(Variable*, Expression*);
  Statement* if_else(Expression* test, Statement*, Statement*);
  Statement* while_stmt(Expression* test, Statement* body);
  Expression* addop(Expression*, Expression*); // binary operators type 1
  Expression* subop(Expression*, Expression*);
  Expression* mulop(Expression*, Expression*);
  Expression* divop(Expression*, Expression*);
  Expression* andop(Expression*, Expression*); // binary operators type 2
  Expression* orop(Expression*, Expression*);
  Expression* xorop(Expression*, Expression*);
  Expression* div2op(Expression*, Expression*);
  Expression* modop(Expression*, Expression*);
  Expression* eqop(Expression*, Expression*); // binary operators type 3
  Expression* neop(Expression*, Expression*);
  Expression* ltop(Expression*, Expression*);
  Expression* leop(Expression*, Expression*);
  Expression* gtop(Expression*, Expression*);
  Expression* geop(Expression*, Expression*);
  Expression* Context::negop(Expression*); // unary ops
  Expression* Context::notop(Expression*);

protected:
  VariableExpression* get_varexpr(Type*);
  Expression* binop1(Quadruple::Op, Quadruple::Op, Expression*, Expression*);
  Expression* binop2(Quadruple::Op, Expression*, Expression*);
  Expression* binop3(Quadruple::Op, Quadruple::Op, Expression*, Expression*);

};

// Globals

extern int label;		// next label

// lexical tie-in, keeps track of current context
extern Context *context;

Context* init_toplevel();

// construct a parameter
TypeList *make_parameter(SymbolList&, Type *);

/*
class Function : public Context
{
public:
  TypeList* formal_parameters;
  Type* return_type;

  Function() {}
};
*/
#endif










