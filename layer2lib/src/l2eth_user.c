/*****************************************************************************/
/*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.*/
/*****************************************************************************/
/*  F i l e                l2eth_user.c                                      */
/*****************************************************************************/
/*  This module contains the common dual port RAM functions. There are       */
/*  no os dependent functions.                                               */
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

#include "os.h"
#include "cp16xx.h"

#include "l2eth_config.h"
#include "l2eth_errs.h"
#include "l2eth_user.h"
#include "l2eth_rqb.h"
#include "l2eth_base.h"

#ifndef __KERNEL__
#include "tracemcr.h"
#endif

/* exported functions */
#ifdef MANAGED_CP_EXCHANGE
extern "C" L2ETH_UINT32 L2ETH_CODE_ATTR ldah_check(L2ETH_UINT32 CpIndex);
#endif

/*===========================================================================
*    critical section
*==========================================================================*/
#ifdef __KERNEL__
    #define L2_MUTEX_CREATE_UNLOCKED
    #define L2_MUTEX_LOCK
    #define L2_MUTEX_UNLOCK
    #define L2_MUTEX_DESTROY
#else
    L2ETH_MUTEX L2MutexUser;
    #define L2_MUTEX_CREATE_UNLOCKED L2ETH_MUTEX_CREATE_UNLOCKED(L2MutexUser)
    #define L2_MUTEX_LOCK L2ETH_MUTEX_LOCK(L2MutexUser)
    #define L2_MUTEX_UNLOCK L2ETH_MUTEX_UNLOCK(L2MutexUser)
    #define L2_MUTEX_DESTROY L2ETH_MUTEX_DESTROY(L2MutexUser)
#endif

void InitL2CriticalSections(void)
{
    L2_MUTEX_CREATE_UNLOCKED;
}

void DestroyL2CriticalSections(void)
{
    L2_MUTEX_DESTROY;
}
/*===========================================================================
*    l2eth_open
*==========================================================================*/
L2ETH_UINT32 l2eth_open(L2ETH_UINT32 CpIndex,   /* in */
    L2ETH_CBF_RECEIVE_IND CbfReceiveInd,        /* in */
    L2ETH_CBF_SEND_COMPL CbfSendCompl,  /* in */
    L2ETH_CBF_STATUS_IND CbfStatusInd,  /* in */
    L2ETH_CBF_MODE_COMPL CbfModeCompl,  /* in */
    L2ETH_UINT32 * pHandle /* out: */ )
{
    L2ETH_UINT32 Ret = L2ETH_OK;

    L2_MUTEX_LOCK;

    TRC_OUT01(GR_INIT, LV_FCTPUB1, "->l2eth_open CpIndex %d", CpIndex);

    /* validate cp id */
    if(1 > CpIndex) {
        TRC_OUT(GR_INIT, LV_ERR, " invalid cpid parameter");
        TRC_OUT01(GR_INIT, LV_FCTPUB1, "<- l2eth_open CpIndex %d", CpIndex);
        L2_MUTEX_UNLOCK;
        return L2ETH_ERR_PRM_CP_ID;
    }

    /* call back functions - check for null */
    if(!CbfReceiveInd || !CbfSendCompl || !CbfStatusInd || !CbfModeCompl) {
        TRC_OUT(GR_INIT, LV_ERR, " invalid callback function");
        TRC_OUT01(GR_INIT, LV_FCTPUB1, "<- l2eth_open CpIndex %d", CpIndex);
        L2_MUTEX_UNLOCK;
        return L2ETH_ERR_PRM_PCBF;
    }

#ifdef MANAGED_CP_EXCHANGE
    (void)ldah_check(CpIndex);
#endif

    /* call library open function */
    Ret = l2_open(CpIndex, CbfReceiveInd, CbfSendCompl, CbfStatusInd, CbfModeCompl, pHandle);

    L2_MUTEX_UNLOCK;
    TRC_OUT01(GR_INIT, LV_FCTPUB1, "<- l2eth_open CpIndex %d", CpIndex);

    return Ret;
}

/*===========================================================================
*    l2eth_close
*==========================================================================*/
L2ETH_UINT32 l2eth_close(L2ETH_UINT32 Handle)
{
    l2eth_base *pl2BaseInst;
    L2ETH_UINT32 Ret = L2ETH_OK;

    L2_MUTEX_LOCK;

    TRC_OUT(GR_INIT, LV_FCTPUB1, "->l2eth_close");

    /* get application instance from pointer */
    pl2BaseInst = l2_get_instance(Handle);

    if(pl2BaseInst) {
        /* call library close function */
        Ret = l2_close(pl2BaseInst);
        if(Ret != L2ETH_OK) {
            TRC_OUT(GR_INIT, LV_ERR, "  * l2eth_base Close failed ");
        }
    } else {
        TRC_OUT(GR_INIT, LV_ERR, "  * ERROR getting l2eth_base instance ");
        Ret = L2ETH_ERR_PRM_HND;
    }

    L2_MUTEX_UNLOCK;
    TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_close");

    return Ret;
}

/*===========================================================================
*    l2eth_allocate_packet
*==========================================================================*/
L2ETH_UINT32 l2eth_allocate_packet(L2ETH_UINT32 Handle, /* in */
    L2ETH_PACKET ** ppPacket) /* out */
{
    l2eth_base *pl2BaseInst;
    L2ETH_UINT32 Ret;

    TRC_OUT(GR_INIT, LV_FCTPUB1, "-> l2eth_allocate_packet");

    if(!ppPacket) {
        TRC_OUT(GR_INIT, LV_ERR, "invalid packet parameter");
        TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_allocate_packet");

        return L2ETH_ERR_PRM_PKT;
    }

    /* get application instance from pointer */
    pl2BaseInst = l2_get_instance(Handle);

    if(pl2BaseInst) {
        /* call library allocate packet function */
#ifdef __KERNEL__
        L2_KERNEL_SPINLOCK_FLAGS flags;
        L2_KERNEL_WSPINLOCK_LOCK(Handle, flags);
        Ret = l2_get_allocate_packet(pl2BaseInst, ppPacket);
        L2_KERNEL_WSPINLOCK_UNLOCK(Handle, flags);
#else
        L2_MUTEX_LOCK;
        Ret = l2_get_allocate_packet(pl2BaseInst, ppPacket);
        L2_MUTEX_UNLOCK;
#endif
        if(Ret != L2ETH_OK) {
            TRC_OUT(GR_INIT, LV_ERR, "  * l2eth_allocate_packet failed ");
        }
    } else {
        TRC_OUT(GR_INIT, LV_ERR, "  * ERROR getting l2eth_base instance ");
        Ret = L2ETH_ERR_PRM_HND;
    }

    TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_allocate_packet");

    return Ret;
}

/*===========================================================================
*    l2eth_send
*==========================================================================*/
L2ETH_UINT32 l2eth_send(L2ETH_UINT32 Handle, L2ETH_PACKET * pPacket)
{
    l2eth_base *pl2BaseInst;
    L2ETH_UINT32 Ret;
    /*
       locking is not required
       L2_MUTEX_LOCK;
     */

    //TRC_OUT(GR_INIT, LV_FCTPUB1, "->l2eth_send");

    if(!pPacket) {
        TRC_OUT(GR_INIT, LV_ERR, " invalid packet ");
        TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_send");
        /* L2_MUTEX_UNLOCK; */
        return L2ETH_ERR_PRM_PKT;
    }

    if(!pPacket->pBuffer) {
        TRC_OUT(GR_INIT, LV_ERR, " invalid packet buffer ");
        TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_send");
        /* L2_MUTEX_UNLOCK; */
        return L2ETH_ERR_PRM_BUF;
    }


    /* get application instance from pointer */
    pl2BaseInst = l2_get_instance(Handle);

    if(pl2BaseInst) {
        /* call library send packet function */
        Ret = l2_send_packet(pl2BaseInst, pPacket);
        if(Ret != L2ETH_OK) {
            TRC_OUT(GR_INIT, LV_ERR, "  send failed ");
        }
    } else {
        TRC_OUT(GR_INIT, LV_ERR, "  * ERROR getting l2eth_base instance ");
        Ret = L2ETH_ERR_PRM_HND;
    }

    /*
       locking is not required
       L2_MUTEX_UNLOCK;
     */
    //TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_send");
    return Ret;
}

/*===========================================================================
*    l2eth_free_packet
*==========================================================================*/
L2ETH_UINT32 l2eth_free_packet(L2ETH_UINT32 Handle, L2ETH_PACKET * pPacket)
{
    l2eth_base *pl2BaseInst;
    L2ETH_UINT32 Ret;

    //TRC_OUT(GR_INIT, LV_FCTPUB1, "-> l2eth_free_packet");

    if(!pPacket) {
        TRC_OUT(GR_INIT, LV_ERR, "packet not set");
        TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_free_packet");

        return L2ETH_ERR_PRM_PKT;
    }

    if(!pPacket->pBuffer) {
        TRC_OUT(GR_INIT, LV_ERR, " invalid packet buffer ");
        TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_free_packet");

        return L2ETH_ERR_PRM_BUF;
    }

    /* get application instance from pointer */
    pl2BaseInst = l2_get_instance(Handle);

    if(pl2BaseInst) {
        /* call library free packet function */
#ifdef __KERNEL__
        L2_KERNEL_SPINLOCK_FLAGS flags;
        L2_KERNEL_WSPINLOCK_LOCK(Handle, flags);
        Ret = l2_free_packet(pl2BaseInst, pPacket);
        L2_KERNEL_WSPINLOCK_UNLOCK(Handle, flags);
#else
        L2_MUTEX_LOCK;
        Ret = l2_free_packet(pl2BaseInst, pPacket);
        L2_MUTEX_UNLOCK;
#endif
        if(Ret != L2ETH_OK) {
            TRC_OUT(GR_INIT, LV_ERR, "  *free packet failed ");
        }
    } else {
        TRC_OUT(GR_INIT, LV_ERR, "  * ERROR getting l2eth_base instance ");
        Ret = L2ETH_ERR_PRM_HND;
    }

    //TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_free_packet");
    return Ret;
}


/*===========================================================================
*    l2eth_return_packet
*==========================================================================*/
L2ETH_UINT32 l2eth_return_packet(L2ETH_UINT32 Handle, L2ETH_PACKET * pPacket)
{
    l2eth_base *pl2BaseInst;
    L2ETH_UINT32 Ret;

    TRC_OUT(GR_INIT, LV_FCTPUB1, "-> l2eth_return_packet");

    if(!pPacket) {
        TRC_OUT(GR_INIT, LV_ERR, "packet not set");
        TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_return_packet");

        return L2ETH_ERR_PRM_PKT;
    }

    if(!pPacket->pBuffer) {
        TRC_OUT(GR_INIT, LV_ERR, " invalid packet buffer ");
        TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_return_packet");

        return L2ETH_ERR_PRM_BUF;
    }

    /* get application instance from pointer */
    pl2BaseInst = l2_get_instance(Handle);

    if(pl2BaseInst) {
        /* call library return packet function */
#ifdef __KERNEL__
        L2_KERNEL_SPINLOCK_FLAGS flags;
        L2_KERNEL_RSPINLOCK_LOCK(Handle, flags);
        Ret = l2_return_packet(pl2BaseInst, pPacket, L2ETH_PACKET_OWNER_USER);
        L2_KERNEL_RSPINLOCK_UNLOCK(Handle, flags);
#else
        L2_MUTEX_LOCK;
        Ret = l2_return_packet(pl2BaseInst, pPacket, L2ETH_PACKET_OWNER_USER);
        L2_MUTEX_UNLOCK;
#endif

        if(Ret != L2ETH_OK) {
            TRC_OUT(GR_INIT, LV_ERR, "  *return_packet failed ");
        }
    } else {
        TRC_OUT(GR_INIT, LV_ERR, "  * ERROR getting l2eth_base instance ");
        Ret = L2ETH_ERR_PRM_HND;
    }

    TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_return_packet");
    return Ret;
}



/*===========================================================================
*    l2eth_set_mode
*==========================================================================*/
L2ETH_UINT32 l2eth_set_mode(L2ETH_UINT32 Handle, L2ETH_MODE Mode)
{
    l2eth_base *pl2BaseInst;
    L2ETH_UINT32 Ret;

    L2_MUTEX_LOCK;

    TRC_OUT(GR_INIT, LV_FCTPUB1, "-> l2eth_set_mode");

    if((L2ETH_ONLINE != Mode) && (L2ETH_OFFLINE != Mode)) {
        TRC_OUT(GR_INIT, LV_ERR, "invalid Mode");
        TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_set_mode");

        L2_MUTEX_UNLOCK;
        return L2ETH_ERR_PRM_MODE;
    }

    /* get application instance from pointer */
    pl2BaseInst = l2_get_instance(Handle);

    if(pl2BaseInst) {
        Ret = l2_set_mode(pl2BaseInst, Mode);
        if(Ret != L2ETH_OK) {
            TRC_OUT(GR_INIT, LV_ERR, "BaseInst->setmode failed ");
        }
    } else {
        TRC_OUT(GR_INIT, LV_ERR, " ERROR getting l2eth_base instance ");
        Ret = L2ETH_ERR_PRM_HND;
    }

    L2_MUTEX_UNLOCK;
    TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_set_mode");
    return Ret;
}


/*===========================================================================
*    l2eth_set_information
*==========================================================================*/
L2ETH_UINT32 l2eth_set_information(L2ETH_UINT32 Handle, /* in */
    L2ETH_QUERY * pQuery)
{                               /* in,out */
    l2eth_base *pl2BaseInst;
    L2ETH_UINT32 Ret;

    L2_MUTEX_LOCK;

    TRC_OUT(GR_INIT, LV_FCTPUB1, "-> l2eth_set_information");

    if(!pQuery) {
        TRC_OUT(GR_INIT, LV_ERR, "invalid pQuery parameter");
        TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_set_information");

        L2_MUTEX_UNLOCK;

        /* return error */
        Ret = L2ETH_ERR_PRM_QUERY;
        TRC_OUT01(GR_INIT, LV_ERR, "NULL pQuery buffer = 0x%x", Ret);
        return Ret;
    }


    /* check query buffer is null or not */
    if(!pQuery->pBuffer) {
        TRC_OUT(GR_INIT, LV_ERR, "invalid pQuery parameter");
        TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_set_information");

        L2_MUTEX_UNLOCK;

        /* return error */
        Ret = L2ETH_ERR_PRM_BUF;
        TRC_OUT01(GR_INIT, LV_ERR, "NULL pQuery buffer = 0x%x", Ret);
        return Ret;
    }

    /* get application instance from pointer */
    pl2BaseInst = l2_get_instance(Handle);

    if(pl2BaseInst) {
        /* call library set information function */
        Ret = l2_getset_information(pl2BaseInst, SET_INFO, pQuery);
        if(Ret != L2ETH_OK) {
            TRC_OUT(GR_INIT, LV_ERR, "BaseInst->set_information failed ");
        }
    } else {
        TRC_OUT(GR_INIT, LV_ERR, " ERROR getting l2eth_base instance ");
        Ret = L2ETH_ERR_PRM_HND;
    }

    L2_MUTEX_UNLOCK;
    TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_set_information");

    return Ret;
}



/*===========================================================================
*    l2eth_get_information
*==========================================================================*/
L2ETH_UINT32 l2eth_get_information(L2ETH_UINT32 Handle, /* in */
    L2ETH_QUERY * pQuery)
{                               /* in,out */
    l2eth_base *pl2BaseInst;
    L2ETH_UINT32 Ret;

    L2_MUTEX_LOCK;

    TRC_OUT(GR_INIT, LV_FCTPUB1, "-> l2eth_get_information");

    if(!pQuery) {
        TRC_OUT(GR_INIT, LV_ERR, "invalid query parameter");
        TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_get_information");

        L2_MUTEX_UNLOCK;

        /* return error */
        Ret = L2ETH_ERR_PRM_QUERY;
        TRC_OUT01(GR_INIT, LV_ERR, "NULL pQuery = 0x%x", Ret);
        return Ret;
    }

    /* check query buffer is null or not */
    if(!pQuery->pBuffer) {
        L2_MUTEX_UNLOCK;

        /* return error */
        Ret = L2ETH_ERR_PRM_BUF;
        TRC_OUT01(GR_INIT, LV_ERR, "NULL pQuery buffer = 0x%x", Ret);
        return Ret;
    }

    /* get application instance from pointer */
    pl2BaseInst = l2_get_instance(Handle);

    if(pl2BaseInst) {
        /* call library get information function */
        Ret = l2_getset_information(pl2BaseInst, GET_INFO, pQuery);
        if(Ret != L2ETH_OK) {
            TRC_OUT(GR_INIT, LV_ERR, "BaseInst->get_information failed ");
        }
    } else {
        TRC_OUT(GR_INIT, LV_ERR, " ERROR getting l2eth_base instance ");
        Ret = L2ETH_ERR_PRM_HND;
    }

    L2_MUTEX_UNLOCK;
    TRC_OUT(GR_INIT, LV_FCTPUB1, "<- l2eth_get_information");

    return Ret;
}
