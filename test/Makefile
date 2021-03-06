#
# test intermediate code generator
#
# makefile for g++
#
# by eXa/aNaLoG
#

SHELL = /bin/sh

.SUFFIXES:

PROJECT = test

srcdir = .
curdir := $(shell pwd)
parentdir := $(shell cd ..;pwd)
dirname := $(subst $(parentdir)/,,$(curdir))

# Project files

EXEC = test
OBJS = main.o Gen.o
CXXFILES = main.cxx Gen.cxx
INCFILES = main.hxx Gen.hxx Symbol.hxx General.hxx
AFILES =
GRAMMARFILES =
LEXFILES =
LIBS =

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

$(OBJS): General.hxx

main.o: main.cxx Gen.hxx Symbol.hxx
Gen.o: Gen.cxx Gen.hxx Symbol.hxx

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













