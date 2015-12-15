/****************************************************************************
*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.
*****************************************************************************
* FILE NAME    : traceint.cpp
* ---------------------------------------------------------------------------
* DESCRIPTION  : pnio specific trace implementation
*****************************************************************************/

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


#include "os.h"

#include "pniousrx.h"
#include "pniousrd.h"
#include "traceint.h"

#if defined(PC_TRACE_ON) || defined(PRN_TRACE_ON) || defined(WDB_TRACE_ON)

void trcint_ShowAddr(OSTREAM &os, const PNIO_ADDR * add)
{
    if(!add) {
        os << "NULL";
        return;
    }

    os << " IODataType=" << (add->IODataType == PNIO_IO_IN ? "IO_IN" : "IO_OUT");
    os << ", AddrType=";

    if(add->AddrType == PNIO_ADDR_LOG) {
        os << "ADDR_LOG";
        os << ", Addr=" << add->u.Addr;
    }
    /*
     * else if(add->AddrType == PNIO_ADDR_GEO) { os<<"ADDR_GEO"; os<<",
     * addr.GeoAddr.SubnetID="<< add->GeoAddr.SubnetID; os<<",
     * addr.GeoAddr.StatNo="<< add->GeoAddr.StatNo; os<<",
     * addr.GeoAddr.Slot="<< add->GeoAddr.Slot; os<<",
     * addr.GeoAddr.Subslot="<< add->GeoAddr.Subslot; os<<",
     * addr.GeoAddr.Index="<< add->GeoAddr.Index; }
     */
    else {
        os << " (unknown address type !)";
    }
}

void trcint_ShowDAddr(OSTREAM &os, const PNIO_DEV_ADDR *add)
{
    if(!add) {
        os << "NULL";
        return;
    }

    os << " IODataType=" << (add->IODataType == PNIO_IO_IN ? "IO_IN" : "IO_OUT");
    os << ", AddrType=";

    if(add->AddrType == PNIO_ADDR_LOG) {
        os << "ADDR_LOG";
        os << ", Addr=" << add->u.reserved;
    } else if(add->AddrType == PNIO_ADDR_GEO) {
        os << "ADDR_GEO";
        os << ", addr.GeoAddr.Slot=" << add->u.Geo.Slot;
        os << ", addr.GeoAddr.Subslot=" << add->u.Geo.Subslot;
    } else {
        os << " (unknown address type !)";
    }
}

void trcint_ShowData(OSTREAM &os, PNIO_UINT32 Len, const PNIO_UINT8 * Buf)
{
    if(!Buf) {
        os << "NULL";
        return;
    }

    for(PNIO_UINT32 i = 0; i < Len; i++)
        os << (short)Buf[i] << ",";
}

void trcint_ShowDerror(OSTREAM &os, const PNIO_ERR_STAT * err)
{
    if(!err) {
        os << "NULL";
        return;
    }

    os << showbase << hex;
    os << " Err.ErrCode=" << (short)err->ErrCode;
    os << ", Err.ErrDecode=" << (short)err->ErrDecode;
    os << ", Err.ErrCode1=" << (short)err->ErrCode1;
    os << ", Err.ErrCode2=" << (short)err->ErrCode2;
    os << ", Err.AddValue1=" << (short)err->AddValue1;
    os << ", Err.AddValue2=" << (short)err->AddValue2;

}

void trcint_ShowDiagReq(OSTREAM &os, const PNIO_CTRL_DIAG * diag)
{
    if(!diag) {
        os << "NULL";
        return;
    }

    os << " DiagService=" << diag->DiagService;
    os << ", ReqRef=" << diag->ReqRef;
}

#endif /* PC_TRACE_ON || PRN_TRACE_ON */
