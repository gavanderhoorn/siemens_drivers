#ifndef TRACEINFO_H                    /* ----- reinclude-protection ----- */
#define TRACEINFO_H
/****************************************************************************
* Copyright (C) SIEMENS CORP., 2015 All rights reserved.
* All Rights reserved                                                       *
*****************************************************************************
* FILE NAME    : traceinfo.h
* ---------------------------------------------------------------------------
* DESCRIPTION  : Subsystem definitions for firmware trace
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


#define EXCEPTION_BUFFER_START  0x504100UL
#define EXCEPTION_BUFFER_LENGTH 0x4000UL
#define TRACE_START             0x508100UL
#define TRACE_LENGTH            0xf7f00UL


typedef uint32_t TRACE_LINE[4];

typedef struct ltrc_text_info
{
    unsigned long   id;
    unsigned long   id_extension;
    char            name[32];
} LTRC_TEXT_INFO_TYPE;


typedef struct ltrc_buffer_admin
{
    uint32_t    buffer_id;
    uint32_t    size;
    uint32_t    line_number;
    uint32_t    line;
    uint32_t    wr_pos;
    uint32_t    wr_mask;
    uint8_t     is_fixed;
    uint8_t     is_freezed;
} LTRC_BUFFER_ADMIN_TYPE;

const unsigned long TRACE_ADMIN_OFFSET = ((TRACE_LENGTH - sizeof(LTRC_BUFFER_ADMIN_TYPE)) /
                                          sizeof(TRACE_LINE)) * sizeof(TRACE_LINE);


#endif/* of TRACEINFO_H */
