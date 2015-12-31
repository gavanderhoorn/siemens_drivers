/*****************************************************************************/
/*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.*/
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


#ifndef _CNS_E400_H_
#define _CNS_E400_H_

#ifndef WIN32
	#include <inttypes.h>
#endif
typedef uint32_t CNS_UINT32;
typedef uint8_t CNS_UINT8;

#define CNS_FCT_ATTR
#define CNS_MAX_POLL_TIMEOUT 0x00000400UL

void       CNS_FCT_ATTR CnsInOutDone(
    const CNS_UINT8 *IRTE_SWI_BaseAdr);

CNS_UINT32 CNS_FCT_ATTR CnsBlockRead(
    const CNS_UINT8 *IRTE_SWI_BaseAdr,
    const CNS_UINT32 iBlockStart,
    const CNS_UINT32 iBlockLen,
    const CNS_UINT32 PollTimeout);

CNS_UINT32 CNS_FCT_ATTR CnsBlockFreeRead(
    const CNS_UINT8 *IRTE_SWI_BaseAdr,
    const CNS_UINT32 PollTimeout);

CNS_UINT32 CNS_FCT_ATTR CnsBlockWrite(
    const CNS_UINT8 *IRTE_SWI_BaseAdr,
    const CNS_UINT32 iBlockStart,
    const CNS_UINT32 iBlockLen,
    const CNS_UINT32 PollTimeout);

CNS_UINT32 CNS_FCT_ATTR CnsBlockFreeWrite(
    const CNS_UINT8 *IRTE_SWI_BaseAdr,
    const CNS_UINT32 PollTimeout);

typedef void (CNS_FCT_ATTR *CNS_EXCP_FCT) (
    const CNS_UINT32 Line,
    CNS_UINT8 *const sFile,
    const CNS_UINT32 ModuleID,
    CNS_UINT8 *const sErr,
    const CNS_UINT32 Error,
    const CNS_UINT32 DW_0,
    const CNS_UINT32 DW_1);

void       CNS_FCT_ATTR CnsSetExcp(
    CNS_EXCP_FCT const excp_fct);

#endif /* _CNS_E400_H_ */
