/****************************************************************************/
/* Copyright (C) SIEMENS CORP., 2015 All rights reserved.*/
/*                                                                          */
/* file: PNIOUSRT.H                                                         */
/*                                                                          */
/* Description:                                                             */
/*  data types and function declarations for IO-Base controller             */
/*  user interface                                                          */
/*                                                                          */
/****************************************************************************/
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

#ifndef PNIOUSRT_H
#define PNIOUSRT_H

#include "pniobase.h"

#undef ATTR_PACKED
#if defined(_MSC_VER)
#pragma pack( push, safe_old_packing, 4 )
#define  ATTR_PACKED
#elif defined(__GNUC__)
#define ATTR_PACKED  __attribute__ ((aligned (4)))
#elif defined(BYTE_ATTR_PACKING)
#include "pack.h"
#define ATTR_PACKED PPC_BYTE_PACKED
#else
#error please adapt pniousrt.h header for your compiler
#endif

#undef PNIO_CODE_ATTR
#ifdef PASCAL
    #define PNIO_CODE_ATTR __stdcall
#else
    #define PNIO_CODE_ATTR
#endif

#ifdef __cplusplus
extern "C" {
#endif
    PNIO_UINT32 PNIO_CODE_ATTR PNIO_data_test(PNIO_UINT32 Handle,      /* in */
        PNIO_UINT8 * pBuffer,   /* in */
        PNIO_UINT32 BufLen     /* in */
        );

    PNIO_UINT32 PNIO_CODE_ATTR PNIO_device_data_test(PNIO_UINT32 Handle,      /* in */
        PNIO_UINT8 * pBuffer,   /* in */
        PNIO_UINT32 BufLen     /* in */
        );
#ifdef __cplusplus
}
#endif
#if defined(_MSC_VER)
#pragma pack( pop, safe_old_packing )
#elif defined(BYTE_ATTR_PACKING)
#include "unpack.h"
#endif

#endif /* PNIOUSRT_H */
