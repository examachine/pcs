/*
** Implementation file for context module
**
** eXa/aNaLoG
**
*/

#include "General.hxx"
#include "Context.hxx"

// make toplevel a subclass of context...
Context* init_toplevel()
{
  return context = new Context(String("main"), 0, 0);
}

// Constructor
Context::Context(String _name, Context* scope, int _depth)
{
  name = _name;
  enclosing = scope;
  depth = _depth;

  qualified_name = (enclosing
		    ? enclosing->qualified_name + "::" + name
		    : name );

  // declare this context
  gen.add(Quadruple(Quadruple::context, 0, 0, this));

  offset=tmp=constant=0;
}
//: offset(0), tmp(0), constant(0) {}


void Context::generate_intermediate_code(Statement* compound)
{
  gen.cat(*compound);
  gen.add(Quadruple(Quadruple::ret, 0, 0, 0));
  gen.emit(cout);
}

// get local offset for a given type
int Context::get_offset(Type *t)
{
  int ret=offset;
  offset += t->storage();
  return ret;
}

// get number of next temporary variable expression
int Context::get_tmp() { return tmp++; }

// fetch a new label
Label* Context::get_label() { return new Label(label++); }

// declare local variables of the same type
void Context::declare_variables(SymbolList& variables, Type* type)
{
  for (SymbolTrav i=variables.beg_head(); i.state(); i.succ()) {
    if (symbol_table.lookup(variables[i]->name)) {
      cout << "Duplicate declaration of identifier" << endl;
    }
    else {
      Variable *variable = new Variable(variables[i]->name,
					type, get_offset(type));
      symbol_table.insert(variable);
      type->declare_local(&gen, variable);
    }
  }
}

// construct a variable expression from given variable
VariableExpression* Context::get_varexpr(Variable *v)
{
  VariableExpression *expr = new VariableExpression(v);
  Symbol* expr2;

  if (expr2=symbol_table.lookup(expr->name))
    return dynamic_cast<VariableExpression*>(expr2);
  else {
    // first reference
    symbol_table.insert(expr);
    return expr;
  }
}

// get a temporary
VariableExpression* Context::get_varexpr(Type *t)
{
  VariableExpression *expr = new VariableExpression(get_tmp(), t,
						    get_offset(t));
  symbol_table.insert(expr);
  return expr;
}

ConstantExpression* Context::get_constexpr(int v)
{
  ConstantExpression *expr = new ConstantExpression(constant++, v);
  symbol_table.insert(expr);
  return expr;
}

ConstantExpression* Context::get_constexpr(double v)
{
  ConstantExpression *expr = new ConstantExpression(constant++, v);
  symbol_table.insert(expr);
  return expr;
}

// get a constant expression with indicated type and data
ConstantExpression* Context::get_constexpr(Type *t, void *v)
{
  ConstantExpression *expr = new ConstantExpression(constant++, t, v);
  symbol_table.insert(expr);
  return expr;
}

// make a constant expression from a constant
ConstantExpression* Context::get_constexpr(Constant *c)
{
  ConstantExpression *expr = new ConstantExpression(get_tmp(), c);
  symbol_table.insert(expr);
  return expr;
}

// reference a variable
Variable* Context::variable_ref(Symbol *identifier)
{
  if (Symbol* sym = symbol_table.lookup(identifier->name)) {
    if (typeid(*sym)==typeid(Variable))
      return dynamic_cast<Variable*>(sym);
    else
      cout << "cannot be referenced as a variable" << endl;
  }
  else
    cout << "variable not declared" << endl;
}

// Assignment operation
// integers are automatically coerced into reals
Statement* Context::assign(Variable* lval, Expression* rval)
{
  Statement* stmt = new Statement;
  stmt->cat(rval->gen);

  if (lval->is_integer())
    if (rval->is_integer()) {
      stmt->add(Quadruple(Quadruple::move, rval, 0, lval));
      return stmt;
    }

  if (lval->is_real())
    if (rval->is_integer()) {
      VariableExpression* temp = get_varexpr(new RealType);
      stmt->add(Quadruple(Quadruple::inttofloat, rval, 0, temp));
      stmt->add(Quadruple(Quadruple::movef, temp, 0, lval));
      return stmt;
    }
    else
      if (rval->is_real()) {
	stmt->add(Quadruple(Quadruple::movef, rval, 0, lval));
	return stmt;
      }

  cout << "Type mismatch" << endl;

}

Statement* Context::if_else(Expression* test, Statement* if_true,
			    Statement* if_false)
{
  IfElseStatement* stmt = new IfElseStatement;
  stmt->if_else = get_label();
  stmt->end = get_label();
  stmt->cat(test->gen);

  if (test->is_integer()) {
    stmt->add(Quadruple(Quadruple::jeqz, test, 0, stmt->if_else));
    stmt->cat(*if_true);
    stmt->add(Quadruple(Quadruple::jmp, 0, 0, stmt->end));
    stmt->add(Quadruple(Quadruple::label, 0, 0, stmt->if_else));
    stmt->cat(*if_false);
    stmt->add(Quadruple(Quadruple::label, 0, 0, stmt->end));
    return stmt;
  }

  cout << "Type Mismath" << endl;
}

Statement* Context::while_stmt(Expression* test, Statement* body)
{
  Statement* stmt = new Statement;
  stmt->start = get_label();
  stmt->end = get_label();

  if (test->is_integer()) {
    stmt->add(Quadruple(Quadruple::label, 0, 0, stmt->start));
    stmt->cat(test->gen);
    stmt->add(Quadruple(Quadruple::jeqz, test, 0, stmt->end));
    stmt->cat(*body);
    stmt->add(Quadruple(Quadruple::jmp, 0, 0, stmt->start));
    stmt->add(Quadruple(Quadruple::label, 0, 0, stmt->end));
    return stmt;
  }

  cout << "Type Mismath" << endl;
}

// Binary operation type 1:
// Integer x Integer -> Integer
// Real x Real -> Real
// integers are coerced into reals where appropriate
Expression* Context::binop1(Quadruple::Op op, Quadruple::Op opf,
			    Expression* a, Expression* b)
{
  VariableExpression *expr, *temp;

  if (a->is_integer())
    if (b->is_integer()) {
      expr = get_varexpr(new IntegerType);
      expr->gen.cat(a->gen);
      expr->gen.cat(b->gen);
      expr->gen.add(Quadruple(op, a, b, expr));
      return expr;
    }
    else
      if (b->is_real()) {
	temp = get_varexpr(new RealType);
	expr = get_varexpr(new RealType);
	expr->gen.cat(a->gen);
	expr->gen.cat(b->gen);
	expr->gen.add(Quadruple(Quadruple::inttofloat, a, 0, temp));
	expr->gen.add(Quadruple(opf, temp, b, expr));
	return expr;
      }

  if (a->is_real())
    if (b->is_integer()) {
      temp = get_varexpr(new RealType);
      expr = get_varexpr(new RealType);
      expr->gen.cat(a->gen);
      expr->gen.cat(b->gen);
      expr->gen.add(Quadruple(Quadruple::inttofloat, b, 0, temp));
      expr->gen.add(Quadruple(opf, a, temp, expr));
      return expr;
    }
    else
      if (b->is_real()) {
	expr = get_varexpr(new RealType);
	expr->gen.cat(a->gen);
	expr->gen.cat(b->gen);
	expr->gen.add(Quadruple(opf, a, b, expr));
	return expr;
      }
  
  cout << "Type mismatch" << endl;
}

// Binary operation type 2:
// Integer x Integer -> Integer
Expression* Context::binop2(Quadruple::Op op,
			    Expression* a, Expression* b)
{
  VariableExpression *expr;

  if (a->is_integer() && b->is_integer()) {
    expr = get_varexpr(new IntegerType);
    expr->gen.cat(a->gen);
    expr->gen.cat(b->gen);
    expr->gen.add(Quadruple(op, a, b, expr));
    return expr;
  }
  
  cout << "Type mismatch" << endl;
}

// Binary operation type 3:
// Comparison operators
// return integer 0 if fail, nonzero if true
// Integer x Integer -> Integer
// Real x Real -> Integer
// integers are coerced into reals where appropriate
Expression* Context::binop3(Quadruple::Op op, Quadruple::Op opf,
			    Expression* a, Expression* b)
{
  VariableExpression *expr = get_varexpr(new IntegerType), *temp;
  expr->gen.cat(a->gen);
  expr->gen.cat(b->gen);
 
  if (a->is_integer())
    if (b->is_integer()) {
      expr->gen.add(Quadruple(op, a, b, expr));
      return expr;
    }
    else
      if (b->is_real()) {
	temp = get_varexpr(new RealType);
	expr->gen.add(Quadruple(Quadruple::inttofloat, a, 0, temp));
	expr->gen.add(Quadruple(opf, temp, b, expr));
	return expr;
      }

  if (a->is_real())
    if (b->is_integer()) {
      temp = get_varexpr(new RealType);
      expr->gen.add(Quadruple(Quadruple::inttofloat, b, 0, temp));
      expr->gen.add(Quadruple(opf, a, temp, expr));
      return expr;
    }
    else
      if (b->is_real()) {
	expr->gen.add(Quadruple(opf, a, b, expr));
	return expr;
      }
  
  cout << "Type mismatch" << endl;
}

// Negation operation
// Integer -> Integer
// Real -> Real
Expression* Context::negop(Expression* a)
{
  VariableExpression *expr;

  if (a->is_integer()) {
    expr = get_varexpr(new IntegerType);
    expr->gen.cat(a->gen);
    expr->gen.add(Quadruple(Quadruple::neg, a, 0, expr));
    return expr;
  }

  if (a->is_real()) {
    expr = get_varexpr(new RealType);
    expr->gen.cat(a->gen);
    expr->gen.add(Quadruple(Quadruple::negf, a, 0, expr));
    return expr;
  }
  
  cout << "Type mismatch" << endl;
}

// Logical Not
// Integer -> Integer
Expression* Context::notop(Expression* a)
{
  VariableExpression *expr;

  if (a->is_integer()) {
    expr = get_varexpr(new IntegerType);
    expr->gen.cat(a->gen);
    expr->gen.add(Quadruple(Quadruple::not, a, 0, expr));
    return expr;
  }
  cout << "Type mismatch" << endl;
}

Expression* Context::addop(Expression* a, Expression* b)
{ return binop1(Quadruple::add, Quadruple::addf, a, b); }

Expression* Context::subop(Expression* a, Expression* b)
{ return binop1(Quadruple::sub, Quadruple::subf, a, b); }

Expression* Context::mulop(Expression* a, Expression* b)
{ return binop1(Quadruple::mul, Quadruple::mulf, a, b); }

Expression* Context::divop(Expression* a, Expression* b)
{ return binop1(Quadruple::div, Quadruple::divf, a, b); }


Expression* Context::andop(Expression* a, Expression* b)
{ return binop2(Quadruple::and, a, b); }

Expression* Context::orop(Expression* a, Expression* b)
{ return binop2(Quadruple::or, a, b); }

Expression* Context::xorop(Expression* a, Expression* b)
{ return binop2(Quadruple::xor, a, b); }

Expression* Context::div2op(Expression* a, Expression* b)
{ return binop2(Quadruple::div, a, b); }

Expression* Context::modop(Expression* a, Expression* b)
{ return binop2(Quadruple::mod, a, b); }


Expression* Context::eqop(Expression* a, Expression* b)
{ return binop3(Quadruple::eq, Quadruple::eqf, a, b); }

Expression* Context::neop(Expression* a, Expression* b)
{ return binop3(Quadruple::ne, Quadruple::nef, a, b); }

Expression* Context::ltop(Expression* a, Expression* b)
{ return binop3(Quadruple::lt, Quadruple::ltf, a, b); }

Expression* Context::leop(Expression* a, Expression* b)
{ return binop3(Quadruple::le, Quadruple::lef, a, b); }

Expression* Context::gtop(Expression* a, Expression* b)
{ return binop3(Quadruple::gt, Quadruple::gtf, a, b); }

Expression* Context::geop(Expression* a, Expression* b)
{ return binop3(Quadruple::ge, Quadruple::gef, a, b); }


int label = 0;			// next label


// construct a parameter
TypeList *make_parameter(SymbolList& param, Type *type)
{
  for (SymbolTrav i=param.beg_head(); i.state(); i.succ()) {
    //Variable *variable = new Variable(variables[i]->name, type, offset);
    //symbol_table.insert(variable);
    //offset += type->storage();
    //type->gen(gen, variable);
  }
  return new TypeList;

}










