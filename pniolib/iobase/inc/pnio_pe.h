/****************************************************************************
*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.
*****************************************************************************
*         FILE : ioconcentrator.h
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

#ifndef _PNIO_PE_H
#define _PNIO_PE_H

#include "os.h"
#include "pnio_pe_util.h"

class ICommon;
class cPeTimer;
class cPeReq;

///////////////////////////////////////////////////////////////////////////////////////
///
///  PROFIenergy Command Manager
///

class cPeMgt {

    //friend class cPnioDrRqb;

    int           m_TickCount;
    //cPeRqQueue    m_PeRqQ(cPeMgt& r); // ref to this class
    cPeRqQueue    m_PeRqQ; // ref to this class

public:
    cPeMgt(IController* pCtrl);
    ~cPeMgt();

    void handleTimerCallback();
    void init();
    void uninit();
    //int  add_pe_request(cPeReq *rq);
    PNIO_UINT32 handle_pe_cmd_request(PNIO_UINT32 Handle, PNIO_ADDR *pAddr, PNIO_REF user_ref, PNIO_PE_REQ_PRM *pPeReqPrm);
    void handle_pe_dr_resp(const t_read_write_dr_resp *pDrRq);
    void handle_pe_dr_read_resp(const t_read_write_dr_resp *pDrRq);
    void handle_pos_read_resp(PNIO_ADDR *pnio_addr, PNIO_REF ReqRef,
                              PNIO_ERR_STAT &e, PNIO_UINT32 len, PNIO_UINT8* pbuff);
    void handle_neg_read_resp(PNIO_ADDR *pnio_addr, PNIO_REF ReqRef, PNIO_ERR_STAT &e,
                              PNIO_UINT32 len, PNIO_UINT8* pbuff);
    void handle_pe_dr_write_resp(const t_read_write_dr_resp *pDrRq);
    void handle_pos_write_resp(PNIO_ADDR *pnio_addr, PNIO_REF user_ref);
    void handle_neg_write_resp(PNIO_ADDR *pnio_addr, PNIO_REF user_rq_ref, PNIO_ERR_STAT &e);
    void increment_req_err_busy_count(PNIO_REF user_rq_ref, PNIO_UINT32 len, PNIO_UINT8* buff);
    void pass_resp_to_user(PNIO_ADDR *pnio_addr, PNIO_REF user_ref, PNAGC_DR_RQ_TYPE dr_rw_action_type,
                           PNIO_ERR_STAT &e, PNIO_UINT32 len, PNIO_UINT8* buff);


    IController  *m_pCtrl;              // back link to outer class
    cPeServiceRef m_PeServiceRef;       // initial size == max size
    cPeTimer     *m_pTimer;             // timer active object (thread)
    PNIO_PE_CBF   m_pUserCbf_PE;        // user PROFIenergy callback function pointer
};



///////////////////////////////////////////////////////////////////////////////////////
///
///
class cPeTimer {

public:
    enum {
        st_idle,
        st_running
    }  m_state;

    cPeMgt         *m_pPeMgt;    // link to parent
    uint16_t        m_TimerId;
    int             m_time_ms;

    static void rawCallback (uint16_t TimerId, cPeTimer* pPeT)
    {
        cPeTimer *p = pPeT;
        p->m_pPeMgt->handleTimerCallback ();
    }

    //friend static DPR_THREAD_RETURN_TYPE DPR_THREAD_DECL peTimerThEntry(void *arg);

public:

    cPeTimer( cPeMgt* p_parent, int t_ms, bool cyclic = true);
    ~cPeTimer();

    void start (void);
    void stop  (void);

    DPR_UINT16             m_stop_thread; /* flag to stop the thread */
    DPR_THREAD_HANDLE      m_th;          /* thread handle */

};  // cPeTimer




#endif /* _PNIO_PE_H  */

