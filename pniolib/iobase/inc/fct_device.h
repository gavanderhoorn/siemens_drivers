/****************************************************************************
*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.
*****************************************************************************
* FILE NAME    : fct_device.h
* ---------------------------------------------------------------------------
* DESCRIPTION  : Device class help structures
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
    PNIO_UINT32          blk_len;
    SYNCHD_CHNL_OP       opcode;
    PNIO_UINT32          handle;    /* in, from IO-Base lib */
    PNIO_DAGENT_RET_TYPE agent_ret; /* if == PNIO_DAGET_RET_OK, analyse resp_ret */
    PNIO_UINT32          resp_ret;

    union {
        t_rqd_open_device         open_device;   /* deprecated */
        t_rqd_open_device_ext     open_device_ext;
        t_resp_open_device        resp_open_device;
        t_rqd_set_dev_state        set_dev_state;
        t_rqd_api_add              api_add;
        t_rqd_api_remove           api_remove;
        t_rqd_set_appl_state_ready set_appl_state_ready;
        t_rqd_device_ar_abort      ar_abort;
        t_rqd_pull                 pull;
        t_rqd_plug                 plug;
        t_rqd_build_channel_properties  build_ch_prop;
        t_rqd_diag_channel_add          diag_ch_add;
        t_rqd_diag_ext_channel_add      diag_ext_ch_add;
        /*t_rqd_diag_generic_add          diag_gen_add;*/ 
        t_rqd_diag_remove               diag_remove;
        /*t_rqd_alarm_send                alarm_send;*/
        t_rqd_ret_of_sub_alarm_send     ret_of_sub_alarm_send;
        t_rqd_test_ping                 test_ping;
    } u;

} ATTR_PACKED light_T_SYNCHD_CHNL; /* this struct was defined to avoid stack consumption,
                                      t_rqd_diag_generic_add and t_rqd_alarm_send have big
                                      static element t_rqd_diag_generic_add::Infodata and
                                      t_rqd_alarm_send::data */

typedef struct {
    PNIO_UINT32 Flink;
    PNIO_UINT32 Blink;
} ATTR_PACKED fw_PNIO_LIST_ENTRY_TYPE;

typedef struct {
    fw_PNIO_LIST_ENTRY_TYPE  ap_list;
} ATTR_PACKED fw_PNIO_APPL_READY_LIST_TYPE;

typedef struct {
    fw_PNIO_LIST_ENTRY_TYPE  link;
    PNIO_UINT32  api;
    fw_PNIO_LIST_ENTRY_TYPE  module_list;
} ATTR_PACKED fw_PNIO_APPL_READY_AP_TYPE;

typedef struct {
    fw_PNIO_LIST_ENTRY_TYPE  link;
    PNIO_UINT16  slot_nr;
    fw_PNIO_LIST_ENTRY_TYPE  submodule_list;
} ATTR_PACKED fw_PNIO_APPL_READY_MODULE_TYPE;

typedef struct {
    fw_PNIO_LIST_ENTRY_TYPE  link;
    PNIO_UINT16  subslot_nr;
} ATTR_PACKED fw_PNIO_APPL_READY_SUBMODULE_TYPE;

typedef  struct {
    PNIO_UINT32  SlotNum;                   /* related slot */
    PNIO_UINT32  SubslotNum;                /* related subslot */
    PNIO_UINT32  reserved;                  /* internal used */
} ATTR_PACKED fw_PNIO_IOCS_TYPE;

typedef struct {
    PNIO_UINT32             CycleTime;
    PNIO_IOCR_TYPE_ENUM     Direction;      /* see PNIO_IOCR_TYPE_ENUM */
    PNIO_IOCR_PROP_ENUM     IOCRProperties; /* see PNIO_IOCR_PROP_ENUM */

    PNIO_UINT32             SendClock;
    PNIO_UINT32             ReductioFactor;
    PNIO_UINT32             Phase;
    PNIO_UINT32             NumOfIoCs;      /* number of IoCs in IoCsList */
    PNIO_UINT32             pIoCsList;      /* ignore pointer to array of IOCS */
    PNIO_UINT32             reserved[3];    /* internal use only */
} ATTR_PACKED fw_PNIO_IOCR_TYPE;

typedef struct {
    PNIO_UINT32           SlotNum;        /* slot number */
    PNIO_UINT32           SubSlotNum;     /* subslot number */
    PNIO_UINT32           SubMProperties; /* module properties */
    PNIO_UINT32           SubMIdent;      /* module ident number */

    PNIO_UINT32           InDatLen;       /* length of the Input data */
    PNIO_UINT32           InIopsLen;      /* length of input provider status */
    PNIO_UINT32           InIocsLen;      /* length of input consumer status */

    PNIO_UINT32           OutDatLen;      /* length of the Output data */
    PNIO_UINT32           OutIopsLen;     /* length of output provider status */
    PNIO_UINT32           OutIocsLen;     /* length of output consumer status */

    PNIO_UINT32           reserved[8];    /* internal use only */

} ATTR_PACKED fw_PNIO_SUBMOD_TYPE;

typedef struct {
    PNIO_UINT32           Api;
    PNIO_UINT32           SlotNum;
    PNIO_UINT32           NumOfSubmod;
    PNIO_UINT32           ModProperties;
    PNIO_UINT32           ModIdent;
    PNIO_UINT32           pSubList;         /* ignore pointer */
} ATTR_PACKED fw_PNIO_MODULE_TYPE;

typedef struct
{
    PNIO_UINT32           pNextAr;          /* ignore pointer */
    PNIO_UINT16           ArNumber;
    PNIO_UINT16           SessionKey;
    PNIO_UINT32           NumOfIocr;
    PNIO_UINT32           pIoCrList;        /* ignore pointer */
    PNIO_UINT32           NumOfMod;
    PNIO_UINT32           pModList;         /* ignore pointer */
} ATTR_PACKED fw_PNIO_AR_TYPE;

#if defined(_MSC_VER)
 #pragma pack( pop, safe_old_packing )
#elif defined(BYTE_ATTR_PACKING)
 #include "unpack.h"
#endif
