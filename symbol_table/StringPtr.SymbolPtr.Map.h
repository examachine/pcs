// This may look like C code, but it is really -*- C++ -*-
/* 
Copyright (C) 1988 Free Software Foundation
    written by Doug Lea (dl@rocky.oswego.edu)

This file is part of the GNU C++ Library.  This library is free
software; you can redistribute it and/or modify it under the terms of
the GNU Library General Public License as published by the Free
Software Foundation; either version 2 of the License, or (at your
option) any later version.  This library is distributed in the hope
that it will be useful, but WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the GNU Library General Public License for more details.
You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
*/


#ifndef _StringPtrSymbolPtrMap_h
#ifdef __GNUG__
#pragma interface
#endif
#define _StringPtrSymbolPtrMap_h 1

#include <Pix.h>
#include "StringPtr.defs.h"

class StringPtrSymbolPtrMap
{
protected:
  int                   count;
  SymbolPtr                   def;

public:
                        StringPtrSymbolPtrMap(SymbolPtr  dflt);
  virtual              ~StringPtrSymbolPtrMap();

  int                   length() const; // current number of items
  int                   empty() const;

  virtual int           contains(StringPtr  key);      // is key mapped?

  virtual void          clear();                 // delete all items

  virtual SymbolPtr&          operator [] (StringPtr  key) = 0; // access contents by key

  virtual void          del(StringPtr  key) = 0;       // delete entry

  virtual Pix           first() = 0;             // Pix of first item or 0
  virtual void          next(Pix& i) = 0;        // advance to next or 0
  virtual StringPtr&          key(Pix i) = 0;          // access key at i
  virtual SymbolPtr&          contents(Pix i) = 0;     // access contents at i

  virtual int           owns(Pix i);             // is i a valid Pix  ?
  virtual Pix           seek(StringPtr  key);          // Pix of key

  SymbolPtr&                  dflt();                  // access default val

  void                  error(const char* msg);
  virtual int           OK() = 0;                // rep invariant
};


inline StringPtrSymbolPtrMap::~StringPtrSymbolPtrMap() {}

inline int StringPtrSymbolPtrMap::length() const
{
  return count;
}

inline int StringPtrSymbolPtrMap::empty() const
{
  return count == 0;
}

inline SymbolPtr& StringPtrSymbolPtrMap::dflt()
{
  return def;
}

inline StringPtrSymbolPtrMap::StringPtrSymbolPtrMap(SymbolPtr  dflt) :def(dflt)
{
  count = 0;
}

#endif
