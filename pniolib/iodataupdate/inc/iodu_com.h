/****************************************************************************
*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.
*****************************************************************************
* FILE NAME    : iodu_com.h
* ---------------------------------------------------------------------------
* DESCRIPTION  : common iodata update
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


#include "pnio_inc.h"

/* ATTENTION !!!!!!
   PNIO_SET/GET_IOXS have in PNIOBASE.H and in PNIO_INC.H
   different representation of GOOD/BAD Status

               PNIO_SET/GET_IOXS      IO-Base Library
   GOOD        >0                     PNIO_S_GOOD = 0
   BAD         0                      PNIO_S_BAD  = 1

   BECAUSE use only IODU_SET/GET_IOXS to be comform with IO-Base Library  */

#define IODU_SET_IOXS(pIoxs, IoxsLen, val, type) \
    PNIO_SET_IOXS(pIoxs, IoxsLen, ((val)==PNIO_S_GOOD) ? 1 : 0, type)
#define IODU_GET_IOXS(pIoxs, IoxsLen) \
    (PNIO_GET_IOXS_DATA_STATE(pIoxs, IoxsLen) ? PNIO_S_GOOD : PNIO_S_BAD)

typedef struct _IODU_CONSUMER_APDU_STATUS
{
  PNIO_UINT16 CycleCount;
  PNIO_UINT8  DataStatus;
  PNIO_UINT8  TransferStatus;
} IODU_CONSUMER_APDU_STATUS;

#define IODU_APDU_DATA_VALID_MASK 0x04
#define IODU_APDU_TRANSFER_MASK 0x0F

#define IODU_GET_CONSUMER_QUALITY(pApduStatus) \
  ( !(((IODU_CONSUMER_APDU_STATUS *)(pApduStatus))->DataStatus & IODU_APDU_DATA_VALID_MASK) ? PNIO_S_BAD : \
      !(((IODU_CONSUMER_APDU_STATUS *)(pApduStatus))->TransferStatus & IODU_APDU_TRANSFER_MASK) ? PNIO_S_BAD : PNIO_S_GOOD)

/* trace macros only for test */
/* #define IODU_TRC_ON */
#ifdef  IODU_TRC_ON
 #include "stdio.h" /* wegen IODU_TRC_X */
 #define IODU_TRC(_p_)    printf _p_ ;
 /* printf("KRAMIOTLB: "s"\n") */
#else
 #define IODU_TRC(_p_)
#endif

