#
# makefile for g++
#
# by exa
#

SHELL = /bin/sh

.SUFFIXES:

PROJECT = cs416prg1

srcdir = .
curdir := $(shell pwd)
parentdir := $(shell cd ..;pwd)
dirname := $(subst $(parentdir)/,,$(curdir))

# Project files

EXEC = lexer
OBJS = Application.o Scanner.o
CXXFILES = Application.cxx Scanner.cxx
CCFILES = 
CFILES =
AFILES =
INCFILES = General.hxx Scanner.hxx Attribute.hxx
LIBS =

IMPLEMENTATION = $(CXXFILES) $(AFILES) $(GRAMMARFILES) $(LEXFILES)
INTERFACE = $(INCFILES)
SRC = $(IMPLEMENTATION) $(INCFILES)
#VER = $(addprefix $(SRC), ,v)
TEST = test.pas test2.pas test3.pas\
       test.out test2.out test3.out
AUX = Makefile $(TEST) disptest
ARCHIVE = $(PROJECT).zip
ARCPATH = ~exa/arc

INCLUDEDIR =
LIBDIR =
PROG = -o $(EXEC)

# Options

CXXOPTIMISE =
CXXDEBUG = -g
CPPFLAGS =
CXXFLAGS = $(CXXDEBUG) $(CXXOPTIMISE)
ASFLAGS =
LDFLAGS = $(CXXDEBUG)

# Programs used

MAKE =	make
CC =	gcc
CXX =	g++
ASM =	as
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

disp%: %.pas $(EXEC)
	@echo Scanning $<
	./$(EXEC) $< #-o $@

# Phony Targets

.PHONY: all compileinfo clean realclean list listsrc listarc extractarc\
	disp*

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

test.out: $(EXEC) test.pas
	./$(EXEC) test.pas
	./$(EXEC) test.pas test.out
test2.out: $(EXEC) test2.pas
	./$(EXEC) test2.pas
	./$(EXEC) test2.pas test2.out
test3.out: $(EXEC) test3.pas
	./$(EXEC) test3.pas
	./$(EXEC) test3.pas test3.out
test4.out: $(EXEC) test4.pas
	./$(EXEC) test4.pas
	./$(EXEC) test4.pas test4.out

# Include automatic dependencies
include $(CXXFILES:.cxx=.d)
include $(CCFILES:.cc=.d)
include $(CFILES:.c=.d)

clean:
	-rm $(OBJS)

realclean:
	-rm $(OBJS) $(EXEC) $(ARCHIVE) *.bak *~

list:
	$(LS) $(SRC) $(AUX)

listsrc:
	$(LS) $(SRC)

# Archive

zip:	$(ARCHIVE)

listzip:
	unzip -l $(ARCHIVE) 

extractzip:
	cd .. ;\
	unzip $(dirname)/$(ARCHIVE)

$(ARCHIVE): $(SRC) $(VER) $(AUX)
	cd .. ;\
	zip -r $(dirname)/$(ARCHIVE) $(addprefix $(dirname)/,$?)

backup:
	$(CP) $(ARCHIVE) $(ARCPATH)/$(ARCHIVE)


