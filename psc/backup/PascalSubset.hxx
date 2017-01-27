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

class Peof : public GTerminal<&Terminals::eof> {
public:
private:
};

class Variables {
public:
  static MetaSymbol Sp;
  static MetaSymbol S;
  static MetaSymbol C;
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



#endif









