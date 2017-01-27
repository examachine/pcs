#
# makefile for g++
#
# Pascal Subset Compiler Project
#
# exa - 1998
#

SHELL = /bin/sh

.SUFFIXES:

PROJECT = psc

srcdir = .
curdir := $(shell pwd)
parentdir := $(shell cd ..;pwd)
dirname := $(subst $(parentdir)/,,$(curdir))

# Project files

EXEC = psc
OBJS = Application.o CFG.o PascalSubset.o Scanner.o \
	Debug.o
CXXFILES = Application.cxx CFG.cxx PascalSubset.cxx Scanner.cxx \
	Debug.cxx Set.cxx
CCFILES = 
CFILES =
AFILES =
INCFILES = General.hxx CFG.hxx PascalSubset.hxx Attribute.hxx Scanner.hxx \
	PSCInterface.hxx Debug.hxx Set.hxx
GRAMMARFILES =
LEXFILES =
LIBS =

IMPLEMENTATION = $(CXXFILES) $(AFILES) $(GRAMMARFILES) $(LEXFILES)
INTERFACE = $(INCFILES)
SRC = $(IMPLEMENTATION) $(INTERFACE)
VERSUFFIX:=,v
#VER = $(addsuffix $(VERSUFFIX), $(SRC))
AUX = Makefile def.cxx def.hxx
ARCHIVE = $(PROJECT).zip
ARCPATH = /home/exa/arc

INCLUDEDIR =
LIBDIR =
PROG = -o $(EXEC)

# Options

CXXOPTIMISE =
CXXDEBUG = #-g
CPPFLAGS =
CXXFLAGS = $(CXXDEBUG) $(CXXOPTIMISE)
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
BACKUP= cp -b
ED =	emacs
LATEX = latex

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
%.dvi : %.tex
	@echo Compiling $<
	@$(LATEX) $<

# Flex - Bison rules

%.tab.c %.tab.h : %.grammar %.hxx
	$(BISON) $< --output-file=$*.tab.c

%.flex.c : %.flex %.tab.h %.hxx
	$(FLEX) -o$@ $<

# Phony Targets

.PHONY: all compileinfo clean realclean list listsrc \
	zip listzip extractzip backup restore

# Default rule

all: defaultmesg compileinfo $(EXEC)

defaultmesg:
	@echo Default rule invoked, building everything

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

clean:
	@echo Deleting object modules and executables
	@-rm $(OBJS) $(EXEC)

distclean: clean
	@echo Deleting archive
	@-rm $(ARCHIVE)

realclean: distclean
	@echo Deleting miscallenous files
	@-rm *.bak *~

list:
	$(LS) $(SRC) $(AUX)

listsrc:
	$(LS) $(SRC)

# Archive

zip:	$(ARCHIVE)

listzip:
	@echo Listing content of ZIP archive
	@unzip -l $(ARCHIVE) 

extractzip:
	@cd .. ;\
	echo Extracting from ZIP archive ;\
	unzip $(dirname)/$(ARCHIVE)

$(ARCHIVE): $(SRC) $(VER) $(AUX)
	@cd .. ;\
	echo Creating ZIP archive ;\
	zip -r $(dirname)/$(ARCHIVE) $(addprefix $(dirname)/,$?)

backup:
	@echo Backing up archive
	@$(BACKUP) $(ARCHIVE) $(ARCPATH)

restore:
	@echo Restoring archive
	@$(CP) $(ARCPATH)/$(ARCHIVE) .


