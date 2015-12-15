/*---------------------------------------------------------------------------*/
/* Copyright (C) SIEMENS CORP., 2015 All rights reserved.*/
/*---------------------------------------------------------------------------*/
/*  Project             : PROFInet Runtime Software                          */
/*  File                : easy_dev_cfg.h                                     */
/*  Version             : V1.0                                               */
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
/*---------------------------------------------------------------------------*/
/*  D e s c r i p t i o n :                                                  */
/*  A few datas for configuration of the simulated device                    */
/*  THIS MODULE HAS TO BE MODIFIED BY THE PNIO USER                          */
/*---------------------------------------------------------------------------*/
/*****************************************************************************/


#define CP_INDEX 1 /* Unique identification for the communication module
                      (module index in the component configuration) */


/***************************************************/
/* PNIO_ANNOTATION entries                         */
/***************************************************/

#define ANNOT_NAME       "CP1616 IRT EASY"  /* device type (String 25) */
#define ANNOT_ORDERID    "0-000-000"        /* Order Id    (String 20) */
#define ANNOT_HW_REV     1                  /* HwRevision  (short)     */
#define ANNOT_SW_PREFIX  'V'                /* SwRevisionPrefix (char) */
#define ANNOT_SW_REV_1   1                  /* SwRevision1 (short)     */
#define ANNOT_SW_REV_2   0                  /* SwRevision2 (short)     */
#define ANNOT_SW_REV_3   0                  /* SwRevision3 (short)     */

/***************************************************/
/* Values for PNIO_device_open                     */
/***************************************************/

#define NUM_OF_SLOTS 8
#define VENDOR_ID    0x002a
#define DEVICE_ID    0x0003
#define INSTANCE_ID  0x0001

/**************************************************/
/* Known diagnose alarms for this device          */
/**************************************************/

#define CH_ERR_INVAL_LINKUP     0x0100
#define CH_ERR_INVAL_LINKDOWN   0x0101
#define CH_ERR_NO_REDUND_PS     0x0200
#define CH_ERR_NO_CPLUG         0x0201
#define CH_ERR_CPLUG_ERROR      0x0202


/****************************************************/
/* help data for pluging of modules and sub modules */
/****************************************************/
typedef struct device_data_s
{
    int         slot;
    int         subslot;
    PNIO_UINT32 modId;
    int         subslotId;
    PNIO_UINT32 api;
    PNIO_UINT16 maxSubslots; /* for internal use. set this to 0 */
    int         modState;    /* for internal use. set this to 0 */
    int         subState;    /* for internal use. set this to 0 */
    int         dir;         /* for internal use, set this to 0 */
} device_data_t;

/*extern device_data_t *device_data;*/

/*  mod     submod  modId   subId   Api                 */
#define DEVICE_DATA \
   { 0,      1,     0x0003, 0x0001, 0x00, 0, 0, 0, 0 }, \
   { 1,      1,     0x0040, 0x0001, 0x00, 0, 0, 0, 0 }, \
   { 2,      1,     0x0043, 0x0001, 0x00, 0, 0, 0, 0 }

#define DEVICE_DATA_ENTRIES  3 /* The total number of members of DEVICE_DATA structure */

/* In order to set tell the application howmany modules and
 * sub modules are known, the above structure and the data
 * described by DEVICE_DATA are to be defined here.
 *
 * If you want more than a submodule for a slot, file DEVICE_DATA
 * as follow:
 *  mod submod  modId   subId   Api
 * { 0,  1,    0x0001, 0x0001, 0x00, 0, 0, 0, 0 }, // device itself
 * { 1,  1,    0x0020, 0x0001, 0x00, 0, 0, 0, 0 }, // module 1 subslot 1
 * { 1,  3,         0, 0x0001, 0x00, 0, 0, 0, 0 }, // module 1 subslot 3
 *
 * The module Id field must be declared for the first entry where
 * this module number appear.
 */
