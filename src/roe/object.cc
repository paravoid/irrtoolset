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
#include "object.hh"
#include "roe_tcl.hh"
#include "roe.hh"
#include "roe_config.hh"
#include "route-list.hh"
#include "irr/irr.hh"
#include "irr/route.hh"  // for class Route

// Added by wlee@isi.edu
extern IRR *whois;

void RoeObject::clear() {
   tcl_Eval(".object.text configure -state normal");
   tcl_Eval(".object.text delete 1.0 end");
   tcl_Eval(".object.text configure -state disabled");
}

void RoeObject::display(char *dbase, ASt as, char *rt) {
   Route *route = NULL;

   tcl_Eval(".object.text configure -state normal");
   tcl_Eval(".object.text delete 1.0 end");
   //   tcl_Eval(".object.buttons.add configure -state normal");
   tcl_Eval(".object.buttons.delete configure -state normal");
   tcl_Eval(".object.buttons.update configure -state normal");
   tcl_Eval(".object.buttons.schedule configure -state normal");

   // Modified by wlee@isi.edu
   //   whois->QueryKillResponse("!ufo=1");
   //   whois->QueryKillResponse("!uF=0");
   whois->setFullObjectFlag(true);
   whois->setFastResponseFlag(false);

   whois->SetSources(dbase);
   // Modified by wlee@isi.edu
   //   int code = whois->QueryResponse(buffer, "!mrt,%s-AS%d", rt, as);
   whois->getRoute(route, rt, as);

   whois->SetSources();

   // Modified by wlee@isi.edu
   //   if (code)
   if (route) {
      tcl_Eval(".object.text insert 1.0 {%.*s}", route->size, route->contents);
      delete route;
   }

   tcl_Eval(".object.text configure -state disabled");
}

void RoeObject::del(int index) {
   char buffer[64];
   RouteList::Route *vr = routelist(index);

   // Modified by wlee@isi.edu
   tcl_Eval("set AS AS%d", routelist.as);
   //   tcl_Eval("set AS %s", routelist.as);
   tcl_Eval("set ROUTE %s", vr->route.get_text(buffer));
   tcl_Eval("set DATE %s", configure.date);

   tcl_Eval(".object.text configure -state normal");
   tcl_delete_matching_lines(".object.text", "^delete:");
   tcl_Eval(".object.text insert end \"%s\"", configure.del_template);
   tcl_Eval("focus .object.text");
}

void RoeObject::add(int index) {
   char buffer[64];
   RouteList::Route *vr = routelist(index);

   // Modified by wlee@isi.edu
   tcl_Eval("set AS AS%d", routelist.as);
   //   tcl_Eval("set AS %s", routelist.as);
   tcl_Eval("set ROUTE %s", vr->route.get_text(buffer));
   tcl_Eval("set DATE %s", configure.date);

   tcl_Eval(".object.text configure -state normal");
   tcl_Eval(".object.text delete 1.0 end");
   tcl_Eval(".object.text insert end \"%s\"", configure.add_template);
   tcl_Eval("focus .object.text");
   tcl_Eval(".object.buttons.schedule configure -state normal");
}

void RoeObject::upd(int index) {
   char buffer[64];
   RouteList::Route *vr = routelist(index);

   // Modified by wlee@isi.edu
   tcl_Eval("set AS AS%d", routelist.as);
   //   tcl_Eval("set AS %s", routelist.as);
   tcl_Eval("set ROUTE %s", vr->route.get_text(buffer));
   tcl_Eval("set DATE %s", configure.date);

   tcl_Eval(".object.text configure -state normal");
   tcl_delete_matching_lines(".object.text", "^changed:");
   tcl_Eval(".object.text insert end \"%s\"", configure.upd_template);
   tcl_Eval("focus .object.text");
}