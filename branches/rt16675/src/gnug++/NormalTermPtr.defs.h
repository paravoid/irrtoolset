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


#ifndef _NormalTermPtrdefs_h
#define _NormalTermPtrdefs_h 1

#include "config.h"
#include "normalform/NT.hh"

// equality operator
#ifndef NormalTermPtrEQ
#define NormalTermPtrEQ(a, b)  ((*a) == (*b))
#endif

// less-than-or-equal
#ifndef NormalTermPtrLE
#define NormalTermPtrLE(a, b)  ((*a) <= (*b))
#endif

// comparison : less-than -> < 0; equal -> 0; greater-than -> > 0
#ifndef NormalTermPtrCMP
#define NormalTermPtrCMP(a, b) ( ((*a) <= (*b))? (((*a) == (*b))? 0 : -1) : 1 )
#endif

// hash function
#ifndef NormalTermPtrHASH
extern unsigned int hash(NormalTermPtr );
#define NormalTermPtrHASH(x)  hash(x)
#endif

// initial capacity for structures requiring one

#ifndef DEFAULT_INITIAL_CAPACITY
#define DEFAULT_INITIAL_CAPACITY 100
#endif

// HASHTABLE_TOO_CROWDED(COUNT, SIZE) is true iff a hash table with COUNT
// elements and SIZE slots is too full, and should be resized.
// This is so if available space is less than 1/8.

#define HASHTABLE_TOO_CROWDED(COUNT, SIZE) ((SIZE) - ((SIZE) >> 3) <= (COUNT))

#endif
