/****************************************************************************
*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.
*****************************************************************************
* FILE NAME    : transferwd.h
* ---------------------------------------------------------------------------
* DESCRIPTION  : Transfer watchdog implementation
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
/*****************************************************************************/
#ifndef TRANSFERWD_H_
#define TRANSFERWD_H_

#include "pniointr.h"

class IController;

class CTransferWD
{
public:
    CTransferWD();
    virtual ~CTransferWD();

    bool Init(IoConcentrator * pIoc, IController * pController);
    void Uninit();
    void Clock(PNIO_CP_CBE_PRM * prm);

    // Interface to KRAM and Cache Flags
    void CacheSet(PNIO_UINT32 addr);        /* set flag "cache is up to date" of specified submodule */
    void CacheSet();                        /* set flag "cache is up to date" of all submodules */
    void CacheReset(PNIO_UINT32 addr);      /* reset flag "cache is up to date" of specified submodule */
    void CacheReset();                      /* reset flag "cache is up to date" of all submodules */
    void KramSet(PNIO_UINT32 addr);         /* set flag "KRAM is up to date" of specified submodule */
    void KramSet();                         /* set flag "KRAM is up to date" of all submodules */
    void KramReset(PNIO_UINT32 addr);       /* reset flag "KRAM is up to date" of specified submodule */
    void KramReset();                       /* reset flag "KRAM is up to date" flag of all submodules */
    bool IsCacheSet(PNIO_UINT32 addr);      /* return true if flag "cache is up to date" of specified submodule is set */

private:

    typedef struct
    {
        bool        cacheSet;
        bool        kramSet;
    }
    TIME_MON_ENTRY_TYPE;

    typedef struct
    {
        PNIO_UINT32            addr;            // logical address
        TIME_MON_ENTRY_TYPE *  pTimeMonEntry;  // pointer to element in timeout monitor array
    }
    TIME_MON_INDEX_ENTRY_TYPE;

    typedef enum {
        TWD_INIT,         // Initial state
        TWD_WAIT_WD_TIME, // Waiting for valid watchdog time in conc table
        TWD_READY,        // Ready for monitor start
        TWD_RUN,          // Monitoring modules...
        TWD_STOP,         // Monitoring stopped, buffers still allocated, ready for monitor restart
        TWD_UNINIT        // Uninitializing, deallocating buffers
    } TWD_STATE_TYPE;

    static const PNIO_UINT32 m_pollRate = 5;

    void                InitWatchdogTimer(void);
    void 				CacheResetNoLock();                
    void 				KramResetNoLock();                 
    IoConcentrator *    m_pIoc;                     // Pointer to io-concentrator instance
    IController    *    m_pController;              // Pointer to controller instance

    // Timeout monitor array - contains all sliced modules
    // Index is logical address
    TIME_MON_ENTRY_TYPE * m_pTimeMon;               
    // Index array - used for fast iteration over all sliced modules.
    // Elements contain pointers to the sliced submodules in timeout monitor array
    // Index of index array is NOT logical address of submodules
    TIME_MON_INDEX_ENTRY_TYPE * m_pTimeMonIndex;    

    PNIO_UINT32 m_NumOfIocHostModulePerCycle;
    PNIO_UINT32 m_actIocHostModuleIndex;

    PNIO_UINT32 m_NumOfIocHostModules;  // number of sliced modules
    PNIO_UINT32 m_MaxIocHostModuleAddr; // largest logical address of sliced modules

    PNIO_UINT32 m_reduction;            // reduction ratio of new cycle interrupt
    PNIO_UINT32 m_clockCount;           // reduction counter (counts 0,1,...,m_reduction,0,1,....)
    PNIO_UINT32 m_wdTime;               // watchdog interval
    PNIO_UINT32 m_newCycleIrqTime;      // new cycle interrupt interval

    TWD_STATE_TYPE  m_state;            // internal transfer watchdog state
};

#endif /*TRANSFERWD_H_*/
