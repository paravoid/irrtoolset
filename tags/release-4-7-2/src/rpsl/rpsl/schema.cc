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

#include "config.h"

#include <cstring>
#include <cstdio>
#include "gnu/std.h"

#include "object.hh"
#include "schema.hh"

Schema::~Schema()  {
   for (int i = 0; i < lastClass; ++i)
      delete classes[i];
   if (dictionary)
      delete dictionary;
}

AttrClass* Schema::searchClass(const char *name) {
   for (int i = 0; i < lastClass; ++i)
      if (!strcasecmp(name, classes[i]->name)) {
	 classes[i]->touch();
	 classes[i]->reset();
	 return classes[i];
      }

   return NULL;
}

void Schema::printClassStats() {
   for (int i = 0; i < lastClass; ++i)
      cout << classes[i]->name << " " << classes[i]->ref_cnt << "\n";
}

int Schema::searchKeyword(const char *word) { // return token_id or -1
   for (int i = 0; keywords[i]._name; i++)
      if (!strcasecmp(keywords[i]._name, word)) {
	 if (!is_context_active || keywords[i].is_reserved)
	    return keywords[i].token_id;
	 else
	    break;
      }

   return -1;
}

int Schema::searchAttrSyntax(const char *word) { // return token_id or -1
   for (int i = 0; attrSyntax[i]._name; i++)
      if (!strcasecmp(attrSyntax[i]._name, word)) {
	 if (!is_context_active || attrSyntax[i].is_reserved)
	    return attrSyntax[i].token_id;
	 else
	    break;
      }

   return -1;
}

RPType* Schema::searchTypedef(const char *name) {
   AttrIterator<AttrTypedef> itr(dictionary, "typedef");
   const AttrTypedef *tdef;

   for (tdef = itr.first(); tdef; tdef = itr.next())
      if (! strcasecmp(tdef->name, name))
	 return tdef->type;

   return NULL;
}

const AttrProtocol* Schema::searchProtocol(const char *name) {
   AttrIterator<AttrProtocol> itr(dictionary, "protocol");
   const AttrProtocol *prot;

   for (prot = itr.first(); prot; prot = itr.next())
      if (! strcasecmp(prot->name, name))
	 return prot;

   return (AttrProtocol *) NULL;
}

const AttrRPAttr *Schema::searchRPAttr(const char *word) { 
   // return token_id or -1
   if (!dictionary)
      return NULL;

   AttrIterator<AttrRPAttr> itr(dictionary, "rp-attribute");
   const AttrRPAttr *attr;

   for (attr = itr.first(); attr; attr = itr.next())
      if (!strcasecmp(attr->name, word))
	 return attr;

   return (AttrRPAttr *) NULL;
}
