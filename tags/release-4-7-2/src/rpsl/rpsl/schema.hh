//  $Id$
//
//  Copyright (c) 1994 by the University of Southern California
//  All rights reserved.
//
//  Permission to use, copy, modify, and distribute this software and its
//  documentation in source and binary forms for lawful non-commercial
//  purposes and without fee is hereby granted, provided that the above
//  copyright notice appear in all copies and that both the copyright
//  notice and this permission notice appear in supporting documentation,
//  and that any documentation, advertising materials, and other materials
//  related to such distribution and use acknowledge that the software was
//  developed by the University of Southern California, Information
//  Sciences Institute. The name of the USC may not be used to endorse or
//  promote products derived from this software without specific prior
//  written permission.
//
//  THE UNIVERSITY OF SOUTHERN CALIFORNIA DOES NOT MAKE ANY
//  REPRESENTATIONS ABOUT THE SUITABILITY OF THIS SOFTWARE FOR ANY
//  PURPOSE.  THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR
//  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE,
//  TITLE, AND NON-INFRINGEMENT.
//
//  IN NO EVENT SHALL USC, OR ANY OTHER CONTRIBUTOR BE LIABLE FOR ANY
//  SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, WHETHER IN CONTRACT, TORT,
//  OR OTHER FORM OF ACTION, ARISING OUT OF OR IN CONNECTION WITH, THE USE
//  OR PERFORMANCE OF THIS SOFTWARE.
//
//  Questions concerning this software should be directed to 
//  ratoolset@isi.edu.
//
//  Author(s): Cengiz Alaettinoglu <cengiz@ISI.EDU>

#ifndef SCHEMA_HH
#define SCHEMA_HH

#include "config.h"
#include <vector>
#include <string>
#include "rptype.hh"
#include "rpsl_attr.hh"

class RPSLKeyword {
   friend class Schema;
private:
   char *_name;		    // token in ASCII, e.g. "accept"
   int  token_id;	    // token as integer, e.g. TKN_ACCEPT
   char is_reserved;        // a reserved word returns token_id to the parser
public:
   RPSLKeyword(char *n, int id, int is_res) : _name(n), token_id(id), 
      is_reserved(is_res) {}
};

class Object;

class Schema {
private:
   static char dictionary_text[];

   int           lastClass;
   AttrClass     *classes[64];
   RPSLKeyword   *keywords;
   RPSLKeyword   *attrSyntax;

   Object  *dictionary;

   bool forgiving;		// if true mandatory/single valued mismatches
				// can be ignored, 
                                // if *very* true (not yet implemented), 
                                // syntax errors can also be ignored
				// key attributes are always non-forgiving

   char is_context_active;  // parsers context may be active
			    // in this context rp_attributes are active
			    // when active, all words return token_id's
			    // to the parser, when non active words return
			    // TKN_WORD to the parser
			    // active context is usually filters and actions
public:
   Schema(RPSLKeyword *_keywords, RPSLKeyword *_attrSyntax) :
      keywords(_keywords), attrSyntax(_attrSyntax), 
      dictionary((Object *) NULL), forgiving(true) {
      lastClass = 0;
   }
   ~Schema();
   void initialize();
   List<Object> *initializeFromFile(char *filename);
   Object *initializeFromString(char *class_text, char *lookFor=(char *) NULL);

   // following searches return NULL/0 on failure
   AttrClass               *searchClass(const char *name); 
   const class  AttrRPAttr *searchRPAttr(const char *name);
   int                      searchKeyword(const char *word);
   RPType                  *searchTypedef(const char *name);
   const AttrProtocol      *searchProtocol(const char *name);   
   int                      searchAttrSyntax(const char *name);
   void                     printClassStats();

   // Added by wlee
   int getLastClass(void) const {
     return lastClass;
   }
   AttrClass *getClass(int i) const {
     return classes[i];
   }

   void beForgiving(bool _forgiving = true) {
      forgiving = _forgiving;
   }
   void beHarsh() {
      forgiving = false;
   }
   bool isForgiving() {
      return forgiving;
   }
   bool isVeryForgiving() {
      return false;
   }

private:
   void initializeBase();
   void addClass(AttrClass *clss);
};

extern Schema schema;

#endif   // SCHEMA_HH