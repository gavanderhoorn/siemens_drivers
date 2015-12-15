/*****************************************************************************/
/* Copyright (C) SIEMENS CORP., 2015 All rights reserved.*/
/*****************************************************************************/
/* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: */
/* 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.                */
/* 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer              */
/* in the documentation and/or other materials provided with the distribution.                                                                    */
/* 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived               */
/* from this software without specific prior written permission.                                                                                  */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,                  */
/* BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT                 */
/* SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES        */
/* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)          */
/* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)              */
/* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                         */
/*****************************************************************************/

#ifndef _TRACE_MCRM_H_
#define _TRACE_MCRM_H_

#ifdef PC_TRACE_ON

#include "tracemcr.h"

/* use CTrcWrapper but not as singelton */
/* to provide instance oriented tracing */
class CTrmWrapper : public CTrcWrapper {
public:
  CTrmWrapper() : CTrcWrapper(){}
  ~CTrmWrapper(){}
};

#define TRM_INIT_FROM_FILE(pI, ConfigFilePath) (pI)->trc_init_from_file(ConfigFilePath);
#define TRM_DEINIT(pI)                         (pI)->trc_deinit(); 
#define TRM_IF_ON(pI, Group, Depth)            (((pI)->dest) && \
                                                     ((Group) & ((pI)->group)) && \
                                                     ((Depth) <= ((pI)->depth)))

#define TRM_IF_ON_EXPR(pI, Group, Depth, _EXPR_)    if(TRM_IF_ON((pI), Group, Depth)) { _EXPR_ }
#define TRM_OUT_OBJECT(pI, Group, Depth, Obj)       if(TRM_IF_ON((pI), Group, Depth)) { (pI)->trc_out((Group), Group##_NAME, (Depth), (Obj).str().data()); }

#define TRM_OUTD(pI, Group, Depth, Data, Len)       if(TRM_IF_ON(pI, Group, Depth)) { (pI)->trc_outd((Group), (Depth), (Data), (Len));}

#define TRM_OUT00(pI, Group, Depth, Msg)            if(TRM_IF_ON(pI, Group, Depth)) { (pI)->trc_outf_((Group), Group##_NAME, (Depth), (Msg));}
#define TRM_OUT01(pI, Group, Depth, Msg, p1)        if(TRM_IF_ON(pI, Group, Depth)) { (pI)->trc_outf_((Group), Group##_NAME, (Depth), (Msg), (p1));}
#define TRM_OUT02(pI, Group, Depth, Msg, p1, p2)    if(TRM_IF_ON(pI, Group, Depth)) { (pI)->trc_outf_((Group), Group##_NAME, (Depth), (Msg), (p1), (p2));}
#define TRM_OUT03(pI, Group, Depth, Msg, p1, p2, p3)    if(TRM_IF_ON(pI, Group, Depth)) { (pI)->trc_outf_((Group), Group##_NAME, (Depth), (Msg), (p1), (p2), (p3));}
#define TRM_OUT04(pI, Group, Depth, Msg, p1, p2, p3, p4)    if(TRM_IF_ON(pI, Group, Depth)) { (pI)->trc_outf_((Group), Group##_NAME, (Depth), (Msg), (p1), (p2), (p3), (p4));}
#define TRM_OUT05(pI, Group, Depth, Msg, p1, p2, p3, p4, p5)    if(TRM_IF_ON(pI, Group, Depth)) { (pI)->trc_outf_((Group), Group##_NAME, (Depth), (Msg), (p1), (p2), (p3), (p4), (p5));}

#else /* PC_TRACE_ON */

#define TRM_INIT_FROM_FILE(pI, ConfigFilePath)  /* empty */
#define TRM_DEINIT(pI)                          /* empty */
#define TRM_IF_ON(pI, Group, Depth)              false

#define TRM_IF_ON_EXPR(pI, Group, Depth, _EXPR_)    /* empty */
#define TRM_OUT(Group, Depth, Msg)      /* empty */
#define TRM_OUT_OBJECT(pI, Group, Depth, Obj)       /* empty */
#define TRM_OUTD(pI, Group, Depth, Data, Len)       /* empty */
#define TRM_OUT00(pI, Group, Depth, Msg)            
#define TRM_OUT01(pI, Group, Depth, Msg, p1)        /* empty */
#define TRM_OUT02(pI, Group, Depth, Msg, p1, p2)    /* empty */
#define TRM_OUT03(pI, Group, Depth, Msg, p1, p2, p3) /* empty */
#define TRM_OUT04(pI, Group, Depth, Msg, p1, p2, p3, p4) /* empty */
#define TRM_OUT05(pI, Group, Depth, Msg, p1, p2, p3, p4, p5) /* empty */
#endif /* PC_TRACE_ON */

#endif /* _TRACE_MCR_H_ */
