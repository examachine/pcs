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
OBJS = main.o pascal_subset.flex.o pascal_subset.tab.o
CXXFILES = main.cxx
INCFILES = main.hxx pascal_subset.hxx
AFILES =
GRAMMARFILES = pascal_subset.grammar
LEXFILES = pascal_subset.flex
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

CXXOPTIMISE =
CXXDEBUG = -g
CPPFLAGS =
CXXFLAGS = $(CXXDEBUG) $(CXXOPTIMISE) -DUSE_LIBGXX_INLINE
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

%.o : %.c
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

main.o: main.cxx main.hxx pascal_subset.tab.h
pascal_subset.flex.o: pascal_subset.flex.c pascal_subset.hxx
pascal_subset.tab.o: pascal_subset.tab.c pascal_subset.hxx

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













