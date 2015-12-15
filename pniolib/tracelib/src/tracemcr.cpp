/****************************************************************************
*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.
*****************************************************************************
* FILE NAME    : tracemcr.cpp
* ---------------------------------------------------------------------------
* DESCRIPTION  : trace module.
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


#define NOTRC
#include "traceout.h"
#include "tracemcr.h"

#ifdef PC_TRACE_ON

CTrcWrapper *CTrcWrapper::_instance = 0;

CTrcWrapper::CTrcWrapper() : CTraceOut()
{
}

CTrcWrapper *CTrcWrapper::Instance()
{
	if(_instance == 0)
		_instance = new CTrcWrapper;
	return _instance;
}

void CTrcWrapper::DestroyInstance()
{
	delete _instance;
	_instance = 0;
}

unsigned long CTrcWrapper::trc_init_from_file(const char * configFile)
{
    long hr = InitFromFile(configFile);

    GetDepth(depth);
    GetGroup(group);
    GetDest(dest);

    trc_outf("Trace init ret=0x%x, depth=0x%lx, group=0x%x", hr, depth, group);

    return hr;
}

void CTrcWrapper::trc_deinit(void)
{
    trc_out(GR_INIT, GET_GR_SNAME(GR_INIT), LV_FCTINT,
        "deinitialise the global trace object");
}

void CTrcWrapper::trc_out(unsigned long Group,
    const char *GrName, unsigned long Depth,
    const char *Msg)
{
    Lock();
    if(dest & 0x00000002)
        printf("D:x%02x %s %s\n", (unsigned int)Depth, GrName, Msg);

    char szBuffer[256];

    snprintf(szBuffer, sizeof (szBuffer), "%s %s%s", GrName,
        (Depth ? "" : "[ERROR] "), Msg);

    OutTraceNotSave(Group, Depth, szBuffer);
    Unlock();
}

void CTrcWrapper::trc_outf_(unsigned long Group,
    const char *GrName, unsigned long Depth,
    const char *szFormat, ...)
{
    char szBuffer[256];
    va_list pArg;

    Lock();

    snprintf(szBuffer, sizeof(szBuffer) - 1, "%s %s ", GrName, (Depth ? "" : "[ERROR]"));
    szBuffer[255] = 0;

    va_start(pArg, szFormat);
    vsnprintf(szBuffer + strlen(szBuffer),
        sizeof (szBuffer) - strlen(szBuffer), szFormat, pArg);
    va_end(pArg);

    OutTraceNotSave(Group, Depth, szBuffer);
    Unlock();
}

void CTrcWrapper::trc_outf(const char *szFormat, ...)
{
    char szBuffer[256];
    va_list pArg;

    Lock();

    va_start(pArg, szFormat);
    vsnprintf(szBuffer, sizeof (szBuffer), szFormat, pArg);
    va_end(pArg);

    OutTraceNotSave(group, depth, szBuffer);
    Unlock();
}

void CTrcWrapper::trc_outd(unsigned long Group,
    unsigned long Depth, unsigned char *Data, long Len)
{
    char Msg[200], Byte[8];
    long i = 0, ii = 1;

    Msg[0] = 0;

    Lock();


    while(i < Len) {

        snprintf(Byte, sizeof(Byte)-1, "%02x ", Data[i]);
        Byte[sizeof(Byte)-1] = 0;
        strncat(Msg, Byte, sizeof(Msg)-1);

        if(ii == 16 || i == (Len - 1)) {
            OutTraceNotSave(Group, Depth, Msg);
            ii = 0;
            Msg[0] = 0;
        }

        i++;
        ii++;
    }

    Unlock();
}

#endif /* PC_TRACE_ON */
