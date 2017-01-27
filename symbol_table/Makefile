#
# CS416 Compiler Design
#
# Project: contexts which allow lexical scoping
#
# makefile for g++
#
# by eXa/aNaLoG
#

SHELL = /bin/sh

.SUFFIXES:

PROJECT = sym_table

srcdir = .
curdir := $(shell pwd)
parentdir := $(shell cd ..;pwd)
dirname := $(subst $(parentdir)/,,$(curdir))

# Project files

EXEC = sym
OBJS = Main.o StringPtr.SymbolPtr.Map.o StringPtr.SymbolPtr.VHMap.o
CXXFILES = Main.cxx Context.cxx
INCFILES = General.hxx Symbol.hxx Type.hxx Variable.hxx Context.hxx \
           SymbolTable.hxx StringPtr.h SymbolPtr.h
AFILES =
GRAMMARFILES =
LEXFILES =
LIBS = -lfl

SRC = $(CXXFILES) $(INCFILES) $(AFILES) $(GRAMMARFILES) $(LEXFILES)
#VER = $(addprefix $(SRC), ,v)
AUX = Makefile
ARCHIVE = $(PROJECT).lzh
ARCPATH = ~exa/arc

INCLUDEDIR =
LIBDIR =
PROG = -o $(EXEC)

# Options

CPPFLAGS =
CXXOPTIMISE =
CXXDEBUG = -g
CXXFLAGS = $(CXXDEBUG) $(CXXOPTIMISE) -frtti -DUSE_LIBGXX_INLINE
ASFLAGS =
LDFLAGS = $(CXXDEBUG)

# Programs used

MAKE =	make
CC =	gcc
CXX =	g++
ASM =	as
BISON =	bison --defines
FLEX =	flex
LS =	ls -l
CP =    cp --interactive
ED =	emacs

# Rules

# Pattern Rules

%.o : %.cxx
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

%.o : %.cc
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

%.tab.c %.tab.h : %.grammar
	$(BISON) $< --output-file=$*.tab.c

%.flex.c : %.flex %.tab.h
	$(FLEX) -o$@ $<


.PHONY: all clean realclean list listsrc listarc extractarc

# Default rule

all:   $(EXEC)

$(EXEC): $(OBJS)
	@echo Building executable: $(EXEC)
	$(CXX) $(LDFLAGS) $(LIBDIR) $(INCLUDEDIR) $(OBJS) $(LIBS) $(PROG)

# dependencies

$(OBJS): General.hxx

Main.o: Main.cxx Type.hxx Symbol.hxx Variable.hxx SymbolTable.hxx\
        StringPtr.SymbolPtr.VHMap.h
#Context.o: Context.cxx Context.hxx

# symbol table created with g++ proto features

StringPtr.h: SymbolPtr.h
StringPtr.defs.h: StringPtr.h
	genclass StringPtr val defs
	cat StringPtr.h StringPtr.defs.h >cat.tmp
	rm StringPtr.defs.h
	mv cat.tmp StringPtr.defs.h

SymbolPtr.h: Symbol.hxx
SymbolPtr.defs.h: SymbolPtr.h
	genclass SymbolPtr val defs
	cat SymbolPtr.h SymbolPtr.defs.h >cat.tmp
	rm SymbolPtr.defs.h
	mv cat.tmp SymbolPtr.defs.h

StringPtr.SymbolPtr.Map.cc StringPtr.SymbolPtr.Map.h: \
  StringPtr.defs.h SymbolPtr.defs.h
	genclass -2 StringPtr val SymbolPtr val Map

StringPtr.SymbolPtr.VHMap.cc StringPtr.SymbolPtr.VHMap.h: \
  StringPtr.defs.h SymbolPtr.defs.h                       \
  StringPtr.SymbolPtr.Map.cc StringPtr.SymbolPtr.Map.h
	genclass -2 StringPtr val SymbolPtr val VHMap

StringPtr.SymbolPtr.Map.o: StringPtr.SymbolPtr.Map.cc StringPtr.SymbolPtr.Map.h
StringPtr.SymbolPtr.VHMap.o: StringPtr.SymbolPtr.VHMap.cc StringPtr.SymbolPtr.VHMap.h


clean:
	-rm $(OBJS)

realclean:
	-rm $(OBJS) $(EXEC) $(ARCHIVE) *.bak *~

list:
	$(LS) $(SRC) $(AUX)

listsrc:
	$(LS) $(SRC)

# Archive

arc:	$(ARCHIVE)

listarc:
	lha l $(ARCHIVE) 

extractarc:
	cd .. ;\
	lha x $(dirname)/$(ARCHIVE)

$(ARCHIVE): $(SRC) $(VER) $(AUX)
	cd .. ;\
	lha u $(dirname)/$(ARCHIVE) $(addprefix $(dirname)/,$?)

backup:
	$(CP) $(ARCHIVE) $(ARCPATH)/$(ARCHIVE)













