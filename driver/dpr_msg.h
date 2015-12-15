/*---------------------------------------------------------------------------
 *  Copyright (C) SIEMENS CORP., 2015 All rights reserved.
 *  Siemens AG. All Rights Reserved.
 *---------------------------------------------------------------------------
 *  Project     : PROFINET IO
 *  Package     : CP1616 DK Firmware
 *  Component   : DPRAM
 *  File        : dpr_msg.h
 *  Date        : 01-Apr-2005
 *
 *---------------------------------------------------------------------------
 *
 *  D e s c r i p t i o n:
 *
 *  Main fuction
 *
 *                Request block declarations for DPRAM channels
 *                ATTENTION: little endian (I386) convention for all values
 *
 *---------------------------------------------------------------------------
 *
 *  H i s t o r y:
 *
 *                2005-04-01 FB first implementation
 *
 *--------------------------------------------------------------------------- */
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



#ifndef _DPR_MSG_H
#define _DPR_MSG_H

/* dpram channel rb header */

typedef struct tag_DPR_MSG_HDR {

    uint32_t hostref;        /* host reference for sequenced communication, do not change on firmware */
    uint8_t  subsystem;      /* subsystem for request */
    uint8_t  reserved1[3];   /* fill bytes */
    uint32_t userid;         /* user id for request, do not change */
    uint32_t response;       /* response */
    uint32_t userdatalength; /* length of the following data */

} DPR_MSG_HDR, * DPR_MSG_HDR_PTR;

/* common response codes for dpram channel rb's, other response codes depend on subsystems */

#define DPR_MSG_HDR_RSP_OK                 ((uint32_t)0)
#define DPR_MSG_HDR_RSP_ILLEGAL_SUBSYSTEM  ((uint32_t)-1)
#define DPR_MSG_HDR_RSP_NO_RESOURCES       ((uint32_t)-2)

/* example of how to use subsystem specific dpram channel rb

typedef struct tag_DPR_MYSUBSYSTEM_RB {
    DPR_MSG_HDR    header;
    uint8_t  mysubsystemdata[SIZE_OF_MYSUBSYSTEMDATA];
} DPR_MYSUBSYSTEM_RB;

DPR_MYSUBSYSTEM_RB *pRb;

pRb->header.userdatalength = SIZE_OF_MYSUBSYSTEMDATA;

*/

#endif /* _DPR_MSG_H */
