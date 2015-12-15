/****************************************************************************
*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.
*****************************************************************************
* FILE NAME    : fct_contr.h
* ---------------------------------------------------------------------------
* DESCRIPTION  : Controller class help structures
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

#include "pniousrd.h"

#undef ATTR_PACKED
#if defined(_MSC_VER)
 #pragma pack( push, safe_old_packing, 4 )
 #define ATTR_PACKED
#elif defined(__GNUC__)
 #define ATTR_PACKED  __attribute__ ((aligned (4)))
#elif defined(BYTE_ATTR_PACKING)
 #include "pack.h"
 #define ATTR_PACKED PPC_BYTE_PACKED
#else
 #error please adapt fct_device.h header for your compiler
#endif

typedef struct {
    PNIO_UINT32       blk_len;
    SYNCH_CHNL_OP     opcode;
    PNIO_UINT32       handle;   // in, will be set by IOBase Lib,
                            //     this handle got IOBase Lib from Agent by OPEN
                            //     in responce case value is undefind
    PNIO_AGETPC_RET_TYPE agent_ret;
    PNIO_UINT32       resp_ret; // only for response


    union {
        t_rq_open_ctrl            open_ctrl;     /* deprecated */
        t_rq_open_ctrl_ext        open_ctrl_ext;
        t_resp_open_ctrl          resp_open_ctrl;
        t_rq_close_ctrl           close_ctrl;
        PNIO_MODE_TYPE            set_mode;
        t_rq_dev_act              dev_state;

        t_ctrl_alarm_confirm      ctrl_al_confirm;
        t_rq_test_ping            test_ping;
        PNIO_CTRL_DIAG            ctrl_diag;
    } u;

} ATTR_PACKED light_T_SYNCH_COMMAND; /* this struct was defined to avoid stack consumption,
                                        see light_T_SYNCHD_CHNL */

#if defined(_MSC_VER)
 #pragma pack( pop, safe_old_packing )
#elif defined(BYTE_ATTR_PACKING)
 #include "unpack.h"
#endif
