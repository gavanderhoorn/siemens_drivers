/*****************************************************************************/
/*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.*/
/*****************************************************************************/
/*  F i l e                dprlib.h                                          */
/*****************************************************************************/
/*  Dualport ring buffer interface functions                                 */
/*****************************************************************************/
/*                                                                           */
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


#ifndef _DPR_LIB_H
#define _DPR_LIB_H

#ifdef __cplusplus
  #define EXTERN_DPR  extern "C"
#else
  #define EXTERN_DPR  extern
#endif

/* error codes */
#define DPR_ERR_INVALID_INTERRUPT           0x82825300   /* unexpeced interrupt type  */
#define DPR_ERR_DPRAM_INIT_INVALID_SIZE     0x82825301  /* InitDPRAM - requested size
                                                           is bigger than available */
#define DPR_ERR_CHNL_INIT_INVALID_SIZE      0x82825302  /* InitChannel - requested size
                                                           is bigger than available */

#define DPR_ERR_FW_SHUTDOWN_REQUEST         0x82825997  /* Shutdown request from FW */
#define DPR_ERR_HOST_SHUTDOWN_REQUEST       0x82825998  /* Shutdown request from Host */
#define DPR_ERR_DPRAM_CRITICAL_ERROR        0x82825999  /* Critical error  */

#define DPR_ERROR 0
#define DPR_OK 1
#define DPR_ALREADY_INITIALIZED 2

#define L2ETH_SEND_CHANNEL_MAX_LENGTH (4080)
#define L2ETH_RECV_CHANNEL_MAX_LENGTH (4080)

/* keep the channels in priority order */
typedef enum  _DPR_CHN_TYPE {
    DPR_PNIO_CMD_CHN = 0,
    DPR_PNIO_ALARM_CHN,
    DPR_PNIO_MOD_CHN,
    DPR_PNIO_DATA_REC_CHN,
    DPR_MGT_CHN,
    DPR_EDDN_HIF_CHN,
    DPR_HIF_CHN,
    DPR_L2_SEND_CHN,
    DPR_L2_RECV_CHN,
    DPR_CFG_MAX_CHANNEL,
    CONTROL_INTERFACE = DPR_CFG_MAX_CHANNEL /* this interface has not a counterpartner in DPR,
                                               it is only for user space/driver communication */
} DPR_CHN_TYPE;

#if (!defined(_DPR_LINUX) && !defined(WIN32))
    typedef uint32_t   DPR_UINT32;
#endif

typedef int(* DPR_READ_CBF)(void * pCP, DPR_CHN_TYPE pChnlType, DPR_UINT32 handle, unsigned long msgLen);

/*===========================================================================
* FUNCTION : DPRLIB_channel_write_message
*----------------------------------------------------------------------------
* INPUTS   : Chnl - channel Index
*            msg - message data
*            msgLen - lenth of message
* OUTPUTS  :
*----------------------------------------------------------------------------
* COMMENTS :
*==========================================================================*/
EXTERN_DPR int DPRLIB_channel_write_message(
    void * pCP,
    DPR_CHN_TYPE Chnl,
    DPR_UINT32 handle,
    void * msg,
    unsigned long msgLen);

/*===========================================================================
* FUNCTION : DPRLIB_channel_register_cbf
*----------------------------------------------------------------------------
* INPUTS   : Chnl - channel Index
*            cbf - callback function pointer
* OUTPUTS  :
*----------------------------------------------------------------------------
* COMMENTS : User must register a callback function for read messages in
*                any channel. User must to copy(allocate and copy) the message
*                into his local list and return ASAP.
*                the momory start address and length is obtaied from the
*                user call back param.
*==========================================================================*/
EXTERN_DPR int DPRLIB_channel_register_cbf(
    void * pCP,
    DPR_CHN_TYPE Chnl,
    DPR_READ_CBF cbf);

/*===========================================================================
* FUNCTION : DPRLIB_channel_read_message
*----------------------------------------------------------------------------
* INPUTS   : Chnl - channel Index
*
* OUTPUTS  : msg - message data buffer
*            msgLen - lenth of message
*----------------------------------------------------------------------------
* COMMENTS : this function is required when the wrapping of ring buffer.
*                caller/cbf must do the allocation of memory before
*                calling this function caller needs to free the memory.
*                the PNIO or other libs need this interface to get the
*                message with out dpr ring wrapping.
*==========================================================================*/
EXTERN_DPR int DPRLIB_channel_read_message(
    void * pCP,
    DPR_CHN_TYPE Chnl,
    void * msg,
    unsigned long msgLen);

/*===========================================================================
* FUNCTION : DPRLIB_start
*----------------------------------------------------------------------------
* INPUTS   :
* OUTPUTS  :
*----------------------------------------------------------------------------
* COMMENTS : This function starts the dpr module
*==========================================================================*/
EXTERN_DPR int DPRLIB_start(
    void * pCP);

/*===========================================================================
* FUNCTION : DPRLIB_stop
*----------------------------------------------------------------------------
* INPUTS   :
* OUTPUTS  :
*----------------------------------------------------------------------------
* COMMENTS : this function is called to make a complete shutdown of the
*            DPR interface. After a call to stop the module can be restarted
*            with DPRLIB_start
*==========================================================================*/
EXTERN_DPR void DPRLIB_stop(
    void * pCP,
    unsigned long errorCode);

/*===========================================================================
* FUNCTION : DPRLIB_restart_req
*----------------------------------------------------------------------------
* INPUTS   :
* OUTPUTS  :
*----------------------------------------------------------------------------
* COMMENTS : this function sends a restart request to the host
*            returns DPR_OK if the messgage could be sent to the host.
*            returns DPR_ERROR if not. Firmware must reset.
*==========================================================================*/
EXTERN_DPR int DPRLIB_restart_req(
    void * pCP);

/*===========================================================================
* FUNCTION : DPRLIB_get_remote_version
*----------------------------------------------------------------------------
* INPUTS   :
* OUTPUTS  :
*----------------------------------------------------------------------------
* COMMENTS : this function is called, to get the word representation from
*            remote version
*==========================================================================*/
EXTERN_DPR DPR_UINT32  DPRLIB_get_remote_version(
    void * pCP);

/*===========================================================================
* FUNCTION : DPRLIB_get_remote_version_as_string
*----------------------------------------------------------------------------
* INPUTS   :
* OUTPUTS  :
*----------------------------------------------------------------------------
* COMMENTS : this function is called, to get the text representation from
*            remote version
*==========================================================================*/
EXTERN_DPR const char *DPRLIB_get_remote_version_as_string(
   void * pCP);

EXTERN_DPR DPR_UINT32 DPRLIB_get_remote_version_as_string_ext(
    void * pCP, char *buf, DPR_UINT32 buflen);

#endif /* _DPR_LIB_H */
