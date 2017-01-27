#
# CS416 Compiler Design
#
# Project: simple compiler for a subset of pascal source language
# which produces intermediate code as quadruples.
#
# makefile for g++
#
# by eXa/aNaLoG
#

SHELL = /bin/sh

.SUFFIXES:

PROJECT = pascal_compiler

srcdir = .
curdir := $(shell pwd)
parentdir := $(shell cd ..;pwd)
dirname := $(subst $(parentdir)/,,$(curdir))

# Project files

EXEC = project
OBJS = main.o pascal_subset.flex.o pascal_subset.tab.o      \
       Context.o Type.o Constant.o Gen.o                    \
       StringPtr.SymbolPtr.Map.o StringPtr.SymbolPtr.VHMap.o
CXXFILES = main.cxx Context.cxx Type.cxx Constant.cxx Gen.cxx
CCFILES =  StringPtr.SymbolPtr.Map.cc StringPtr.SymbolPtr.VHMap.cc
CFILES =   pascal_subset.flex.c pascal_subset.tab.c
INCFILES = General.hxx main.hxx pascal_subset.hxx           \
           Type.hxx Symbol.hxx TypedSymbol.hxx  Label.hxx   \
           Variable.hxx Constant.hxx Expression.hxx         \
           Statement.hxx Gen.hxx Context.hxx                \
           List.hxx SymbolTable.hxx StringPtr.h SymbolPtr.h
AFILES =
GRAMMARFILES = pascal_subset.grammar
LEXFILES = pascal_subset.flex
LIBS = -lfl

IMPLEMENTATION = $(CXXFILES) $(AFILES) $(GRAMMARFILES) $(LEXFILES)
INTERFACE = $(INCFILES)
SRC = $(IMPLEMENTATION) $(INCFILES)
#VER = $(addprefix $(SRC), ,v)
AUX = Makefile test.pas test2.pas test3.pas
ARCHIVE = $(PROJECT).lzh
ARCPATH = ~exa/arc

INCLUDEDIR =
LIBDIR =
PROG = -o $(EXEC)

# Options

CXXOPTIMISE =
CXXDEBUG = -g
CPPFLAGS =
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

# Automatic dependency rules

%.d: %.cxx
	@echo Generating dependencies for $*.cxx
	@$(SHELL) -ec '$(CXX) -MM $(CPPFLAGS) $< \
                 | sed '\''s/$*\\.o[ :]*/& $@/g'\'' > $@'
%.d: %.cc
	@echo Generating dependencies for $*.cc
	@$(SHELL) -ec '$(CXX) -MM $(CPPFLAGS) $< \
                 | sed '\''s/$*\\.o[ :]*/& $@/g'\'' > $@'
%.d: %.c
	@echo Generating dependencies for $*.c
	@$(SHELL) -ec '$(CXX) -MM $(CPPFLAGS) $< \
                 | sed '\''s/$*\\.o[ :]*/& $@/g'\'' > $@'

# Compilation rules

%.o : %.cxx
	@echo Compiling $<
	@$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

%.o : %.cc
	@echo Compiling $<
	@$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

%.o : %.c
	@echo Compiling $<
	@$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

# Flex - Bison rules

%.tab.c %.tab.h : %.grammar %.hxx
	$(BISON) $< --output-file=$*.tab.c

%.flex.c : %.flex %.tab.h %.hxx
	$(FLEX) -o$@ $<


.PHONY: all compileinfo clean realclean list listsrc listarc extractarc

# Default rule

all: compileinfo $(EXEC)

compileinfo:
	@echo C++ flags: $(CXXFLAGS)
	@echo C preprocessor flags: $(CPPFLAGS)

$(EXEC): $(OBJS)
	@echo Building executable: $(EXEC)
	@echo LD flags: $(LDFLAGS)
	@echo Libraries used: $(LIBS)
	@$(CXX) $(LDFLAGS) $(LIBDIR) $(INCLUDEDIR) $(OBJS) $(LIBS) $(PROG)

# Include automatic dependencies
include $(CXXFILES:.cxx=.d)
include $(CCFILES:.cc=.d)
include $(CFILES:.c=.d)

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













