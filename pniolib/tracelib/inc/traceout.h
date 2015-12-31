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
/* DA DIE SOFTWARE IHNEN UNENTGELTLICH UBERLASSEN WIRD, KOENNEN DIE AUTOREN  */
/*****************************************************************************/

#ifndef _TRACE_OUT_H_
#define _TRACE_OUT_H_

#include "os.h"

class CTraceOut {
  public:
    CTraceOut(void);
    virtual ~ CTraceOut(void);

    inline void Lock(void) {
        DPR_MUTEX_LOCK(m_hMutex);
    };

    inline void Unlock(void) {
        DPR_MUTEX_UNLOCK(m_hMutex);
    };

    long GetMaxBackFiles(long &lMaxBackFiles);
    long SetMaxBackFiles(long lMaxBackFiles);
    long GetDest(unsigned  long &lDest);
    long SetDest(unsigned long lDest);
    long GetGroup(unsigned long &);
    long SetGroup(unsigned long);
    long GetFileFast(long &lFileFast);
    long SetFileFast(long lFileFast);
    long GetDepth(unsigned long &);
    long SetDepth(unsigned long);
    long GetFileName(char *szFilename);
    long SetFileName(char *szFilename);

    long InitFromFile(const char *szRegPath);
    long InitFromRegistry(const char *szTraceKey);

    long Rescue(void);

    inline void OutTraceNotSave(unsigned long TraceGroup,
        unsigned long TraceDepth, const char *szMessage) {
        OutTracePrivate(TraceGroup, TraceDepth, szMessage);
    }

  private:

    void OutTracePrivate(unsigned long TraceGroup,
        unsigned long TraceDepth, const char *szMessage);
    long Rename(long lIndex);


    FILE *m_pFile;
    DPR_MUTEX m_hMutex;
    long m_lFileCurrentEntries;
    long m_lCurrentBackFiles;

    unsigned long m_ulDepth;
    unsigned long m_ulGroup;
    long m_lDest;
    long m_lFileFast;
    long m_lFileEntries;
    long m_lMaxBackFiles;
    long m_lTime;
    char m_szFilename[255];
    long m_lPID;
};

const char *TRC_GetFormattedLocalTime(char *szTime, int size);
void TRC_OutputDebugString(const char *txt);

int TRC_ExtractBegin(const char * conffile, char * confpath, int confpathlen);
int TRC_ExtractEnd(void);
unsigned long TRC_ExtractKey(const char *key, char *buffer, int len);

#endif /* _TRACE_OUT_H_ */
