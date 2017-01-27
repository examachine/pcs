/*
**
** Interface file for module
**
**
**
** exa
**
*/

#ifndef PascalSubset_Interface
#define PascalSubset_Interface 1

#include "General.hxx"
#include "CFG.hxx"

class Terminals {
public:
  static MetaSymbol id, intnum, realnum, relop, addop, multop,
    assigop, keyword, delimiter, eof;
};

class Pkeyword : public GTerminal<&Terminals::keyword> {
public:
private:
};

class Pid : public GTerminal<&Terminals::id> {
public:
private:
};

class Pintnum : public GTerminal<&Terminals::intnum> {
public:
private:
};

class Prealnum : public GTerminal<&Terminals::realnum> {
public:
private:
};

class Prelop : public GTerminal<&Terminals::relop> {
public:
private:
};

class Paddop : public GTerminal<&Terminals::addop> {
public:
private:
};

class Pmultop : public GTerminal<&Terminals::multop> {
public:
private:
};
class Passigop : public GTerminal<&Terminals::assigop> {
public:
private:
};
class Pdelimiter : public GTerminal<&Terminals::delimiter> {
public:
private:
};

class Peof : public GTerminal<&Terminals::eof> {
public:
private:
};

class Variables {
public:
  static MetaSymbol Sp;
  static MetaSymbol S;
  static MetaSymbol C;
  static MetaSymbol expression;
  static MetaSymbol simple_expression;
  static MetaSymbol term;
  static MetaSymbol factor;
  static MetaSymbol sign;
};

class PSp : public GVariable<&Variables::Sp> {
public:
private:
};

class PS : public GVariable<&Variables::S> {
public:
private:
};

class PC : public GVariable<&Variables::C> {
public:
private:
};

class Pexpression : public GVariable<&Variables::expression> {
public:
private:
};

class Psimple_expression : public GVariable<&Variables::simple_expression> {
public:
private:
};

class Pterm : public GVariable<&Variables::term> {
public:
private:
};

class Pfactor : public GVariable<&Variables::factor> {
public:
private:
};



#endif









