/****************************************************************************
*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.
*****************************************************************************
* FILE NAME    : pniowd.cpp
* ---------------------------------------------------------------------------
* DESCRIPTION  : user interface functions
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

#include "pniointr.h"

/*
 * global critical section to serialise the dll function calls
 */
DPR_MUTEX PnioMutexWd;
DPR_MUTEX PnioMutexDownload;

/*************************************************************************************
*
* Exported functions
*
**************************************************************************************/

/*===========================================================================
* FUNCTION : PNIO_CP_set_appl_watchdog
*----------------------------------------------------------------------------
* PURPOSE  : With this function an application program registers
*            itself with the Formware Watchdog
*----------------------------------------------------------------------------
* RETURNS  : PNIO_OK on success
*----------------------------------------------------------------------------
* INPUTS   : CpIndex - Unique identification for the communication module
*                      (module index in the component configuration)
*            wdTimeOutInMs - timeout value in milliseconds
*            pnio_appl_wd_cbf - Callback function for signaling the timeout
*----------------------------------------------------------------------------
* COMMENTS :
*==========================================================================*/
PNIO_UINT32 PNIO_CODE_ATTR
PNIO_CP_set_appl_watchdog(PNIO_UINT32 CpIndex,
    PNIO_UINT32 wdTimeOutInMs,
    PNIO_CBF_APPL_WATCHDOG pnio_appl_wd_cbf)
{
    PNIO_UINT32 Ret = PNIO_OK;

    DPR_MUTEX_LOCK(PnioMutexWd);

    TRC_OUT(GR_INIT, LV_FCTPUB1, "->PNIO_CP_set_appl_watchdog");

    TRC_IF_ON_EXPR(GR_INIT, LV_FCTPUB2,
        OSTREAM trcos;
        trcos << showbase << hex;
        trcos << "  CpIndex=" << CpIndex;
        trcos << ", wdTimeOutInMs=" << wdTimeOutInMs;
        trcos << ", pnio_appl_wd_cbf=" << (void *)pnio_appl_wd_cbf;
        trcos << ends;
        TRC_OUT_OBJECT(GR_INIT, LV_FCTPUB2, trcos);
        );

    Ret = ICommon::set_appl_watchdog(CpIndex, wdTimeOutInMs, pnio_appl_wd_cbf);

    TRC_IF_ON_EXPR(GR_INIT, LV_FCTPUB1,
        OSTREAM trcos1;
        trcos1 << showbase << hex;
        trcos1 << "<-PNIO_CP_set_appl_watchdog, ret=" << Ret;
        trcos1 << ends;
        TRC_OUT_OBJECT(GR_INIT, LV_FCTPUB1, trcos1);
        );

    DPR_MUTEX_UNLOCK(PnioMutexWd);

    return Ret;
}

/*===========================================================================
* FUNCTION : PNIO_CP_trigger_watchdog
*----------------------------------------------------------------------------
* PURPOSE  : With this function an application program resets timeout trigger
*----------------------------------------------------------------------------
* RETURNS  : PNIO_OK on success
*----------------------------------------------------------------------------
* INPUTS   : CpIndex - Unique identification for the communication module
*                      (module index in the component configuration)
*----------------------------------------------------------------------------
* COMMENTS :
*==========================================================================*/
PNIO_UINT32 PNIO_CODE_ATTR
PNIO_CP_trigger_watchdog(PNIO_UINT32 CpIndex)
{
    PNIO_UINT32 Ret = PNIO_OK;

    DPR_MUTEX_LOCK(PnioMutexWd);

    TRC_OUT(GR_STATE, LV_FCTPUB1, "->PNIO_CP_trigger_watchdog");

    TRC_IF_ON_EXPR(GR_STATE, LV_FCTPUB2,
        OSTREAM trcos;
        trcos << showbase << hex;
        trcos << "  CpIndex=" << CpIndex;
        trcos << ends;
        TRC_OUT_OBJECT(GR_INIT, LV_FCTPUB2, trcos);
        );

    Ret = ICommon::trigger_watchdog(CpIndex);

    TRC_IF_ON_EXPR(GR_STATE, LV_FCTPUB1,
        OSTREAM trcos1;
        trcos1 << showbase << hex;
        trcos1 << "<-PNIO_CP_trigger_watchdog, ret=" << Ret;
        trcos1 << ends;
        TRC_OUT_OBJECT(GR_INIT, LV_FCTPUB1, trcos1);
        );

    DPR_MUTEX_UNLOCK(PnioMutexWd);

    return Ret;
}

/*===========================================================================
* FUNCTION : PNIO_CP_register_cbf
*----------------------------------------------------------------------------
* PURPOSE  : With this function an application program registers global events
*----------------------------------------------------------------------------
* RETURNS  : PNIO_OK on success
*----------------------------------------------------------------------------
* INPUTS   :
*----------------------------------------------------------------------------
* COMMENTS :
*==========================================================================*/
PNIO_UINT32 PNIO_CODE_ATTR
PNIO_CP_register_cbf(PNIO_UINT32 AppHandle,
        PNIO_CP_CBE_TYPE CbeType,
        PNIO_CP_CBF Cbf)
{
    PNIO_UINT32 Ret = PNIO_OK;

    DPR_MUTEX_LOCK(PnioMutexWd);

    TRC_OUT(GR_STATE, LV_FCTPUB1, "->PNIO_CP_register_cbf");

    TRC_IF_ON_EXPR(GR_STATE, LV_FCTPUB2,
        OSTREAM trcos;
        trcos << showbase << hex;
        trcos << "  AppHandle=" << AppHandle;
        trcos << "  CbeType=" << CbeType;
        trcint_ShowPtr(trcos, (void *)Cbf, "Cbf");
        trcos << ends;
        TRC_OUT_OBJECT(GR_INIT, LV_FCTPUB2, trcos);
        );

        ICommon *pICommonInst = ICommon::get_instance(AppHandle);

    if(pICommonInst) {
        TRC_OUT(GR_INIT, LV_FCTPUB1, " found device instance ");

        Ret = pICommonInst->CP_register_cbf(CbeType, Cbf);
        if(Ret != PNIO_OK) {
            TRC_OUT(GR_INIT, LV_ERR, "  * CP_register_cbf() failed ");
        }
    } else {
        TRC_OUT(GR_INIT, LV_ERR, "  * ERROR getting device instance ");
        Ret = PNIO_ERR_WRONG_HND;
    }

    TRC_IF_ON_EXPR(GR_STATE, LV_FCTPUB1,
        OSTREAM trcos1;
        trcos1 << showbase << hex;
        trcos1 << "<-PNIO_CP_register_cbf, ret=" << Ret;
        trcos1 << ends;
        TRC_OUT_OBJECT(GR_INIT, LV_FCTPUB1, trcos1);
        );

    DPR_MUTEX_UNLOCK(PnioMutexWd);

    return Ret;
}

/*===========================================================================
* FUNCTION : PNIO_CP_set_opdone
*----------------------------------------------------------------------------
* PURPOSE  : With this function an application program
*----------------------------------------------------------------------------
* RETURNS  : PNIO_OK on success
*----------------------------------------------------------------------------
* INPUTS   :
*----------------------------------------------------------------------------
* COMMENTS :
*==========================================================================*/
PNIO_UINT32 PNIO_CODE_ATTR
PNIO_CP_set_opdone(PNIO_UINT32 AppHandle, PNIO_CYCLE_INFO * pCycleInfo)
{
    PNIO_UINT32 Ret = PNIO_OK;

    //DPR_MUTEX_LOCK(PnioMutexWd);

    TRC_OUT(GR_RT, LV_FCTPUB1, "->PNIO_CP_set_opdone");

    TRC_IF_ON_EXPR(GR_RT, LV_FCTPUB2,
        OSTREAM trcos;
        trcos << showbase << hex;
        trcos << "  AppHandle=" << AppHandle;
        trcos << ends;
        TRC_OUT_OBJECT(GR_RT, LV_FCTPUB2, trcos);
        );

        ICommon *pICommonInst = ICommon::get_instance(AppHandle);

    if(pICommonInst) {
        Ret = pICommonInst->CP_set_opdone(pCycleInfo);
    } else {
        Ret = PNIO_ERR_WRONG_HND;
    }

    TRC_IF_ON_EXPR(GR_RT, LV_FCTPUB1,
        OSTREAM trcos1;
        trcos1 << showbase << hex;
        trcos1 << "<-PNIO_CP_set_opdone, ret=" << Ret;
        trcos1 << ends;
        TRC_OUT_OBJECT(GR_RT, LV_FCTPUB1, trcos1);
        );

    //DPR_MUTEX_UNLOCK(PnioMutexWd);

    return Ret;
}

PNIO_UINT32 PNIO_CODE_ATTR
PNIO_CP_cycle_stat(PNIO_UINT32 AppHandle, int MeasureNr, PNIO_CYCLE_STAT * pCycleStat)
{
    PNIO_UINT32 Ret = PNIO_OK;

    //DPR_MUTEX_LOCK(PnioMutexWd);

    ICommon *pICommonInst = ICommon::get_instance(AppHandle);

    if(pICommonInst) {
        Ret = pICommonInst->CP_cycle_stat(pCycleStat,MeasureNr);
    } else {
        Ret = PNIO_ERR_WRONG_HND;
    }

    //DPR_MUTEX_UNLOCK(PnioMutexWd);

    return Ret;


    if (pCycleStat == NULL)     {

    }
}

PNIO_UINT32 PNIO_CODE_ATTR
PNIO_CP_cycle_info(PNIO_UINT32 AppHandle, PNIO_CI_ENTRY * pCycleInfoEntry, int MeasureNr, PNIO_UINT32 Offset)
{
    PNIO_UINT32 Ret = PNIO_ERR_INTERNAL;

    //DPR_MUTEX_LOCK(PnioMutexWd);

    ICommon *pICommonInst = ICommon::get_instance(AppHandle);

    if(pICommonInst) {
        Ret = pICommonInst->CP_cycle_info(pCycleInfoEntry, MeasureNr, Offset);
    } else {
        Ret = PNIO_ERR_WRONG_HND;
    }

    //DPR_MUTEX_UNLOCK(PnioMutexWd);

    return Ret;
}

