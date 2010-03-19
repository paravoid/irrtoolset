//  $Id$
// Copyright (c) 2001,2002                        RIPE NCC
//
// All Rights Reserved
//
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose and without fee is hereby granted,
// provided that the above copyright notice appear in all copies and that
// both that copyright notice and this permission notice appear in
// supporting documentation, and that the name of the author not be
// used in advertising or publicity pertaining to distribution of the
// software without specific, written prior permission.
//
// THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
// ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS; IN NO EVENT SHALL
// AUTHOR BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY
// DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
// AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
//
//  Copyright (c) 1994 by the University of Southern California
//  All rights reserved.
//
//    Permission is hereby granted, free of charge, to any person obtaining a copy
//    of this software and associated documentation files (the "Software"), to deal
//    in the Software without restriction, including without limitation the rights
//    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//    copies of the Software, and to permit persons to whom the Software is
//    furnished to do so, subject to the following conditions:
//
//    The above copyright notice and this permission notice shall be included in
//    all copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//    THE SOFTWARE.
//
//  Questions concerning this software should be directed to
//  irrtoolset@cs.usc.edu.
//
//  Author(s): WeeSan Lee <wlee@ISI.EDU>
//  Author(s): Cengiz Alaettinoglu <cengiz@ISI.EDU>

#ifndef BIRD_HH
#define BIRD_HH

#include "config.h"
#include "irr/irr.hh"
#include "util/net.hh"
#include "util/buffer.hh"
#include "gnug++/SetOfUInt.hh"
#include <cassert>


class BirdWhoisClient : public IRR, public Socket {
  private:
   Buffer *response;

  private:
    bool sendQuery(const char *pzcQuery, ...);
    bool getResponse(char *&text, int &len);
    bool getIndirectMembers(char *sname, const Object *o, char *query, 
			   void (*collect)(void *, const Object *), void *);

  protected:
    virtual bool getAutNum(char *as,          char *&text, int &len);
    virtual bool getSet(SymID sname, char *clss, char *&text, int &len);
    virtual bool getRoute(char *rt, char *as, char *&text, int &len);
    virtual bool getInetRtr(SymID inetrtr,    char *&text, int &len);
    virtual bool expandASSet(SymID asset,     SetOfUInt    *result);
    // REIMP
    virtual bool expandAS(char *as,           MPPrefixRanges *result);
    virtual bool expandRSSet(SymID rsset,     MPPrefixRanges *result);
    virtual bool expandRtrSet(SymID sname,    MPPrefixRanges *result);

  public:
    BirdWhoisClient(void);
    BirdWhoisClient(const char *host, 
		    const int port,
		    const char *sources = dflt_sources);
    virtual void Open(const char *_host = dflt_host, 
		      const int _port = dflt_port, 
		      const char *_sources = dflt_sources);
    virtual void Close(void);

    // For compatibility reasons mostly for roe
    int getSourceOrigin(char *&buffer, const char *rt);
    int getSourceOrigin(char *&buffer);
    void querySourceOrigin(const char *rt);
    bool readReady(void) {
       return (response && response->size > 0) || Socket::readReady();
    }
    ASt getOrigin(char *format, ...);
};

#endif // BIRD_HH