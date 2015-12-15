/****************************************************************************/
/*                                                                          */
/*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.*/
/*                                                                          */
/*    file: l2eth_buf_mgmt.h                                                */
/*                                                                          */
/*    Description:                                                          */
/*    interface function declarations for buffer /packet management         */
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

#ifndef         _L2ETH_BUF_MGMT_H
#define         _L2ETH_BUF_MGMT_H

#ifdef __cplusplus
#ifndef EXTERN
#define EXTERN extern "C"
#endif
#else
#define EXTERN
#endif /* __cplusplus */

/* Function error codes */
typedef enum {
    L2ETH_BUF_SUCCESS,
    L2ETH_BUF_NO_RESOURCES,
    L2ETH_BUF_INVALID_PARAM
} L2ETH_BUF_ERROR;

typedef struct {
    L2ETH_UINT8 *base_address;
    L2ETH_UINT32 buf_size;
    L2ETH_UINT32 buf_cnt;
    L2ETH_UINT8 def_fill;
} L2ETH_BUFFER_DISCRIPTOR;

/*-----------------------------------------------------------------------------------*/
/*                                                                                   */
/*  |<---------------------------L2ETH_BUFFER_CONFIG-------------------------->|     */
/*  |                                                                                */
/*  |<-----BUF DISC----->|<-----AVAIL FLAG ARRAY----->|<-----PACKET BLOCK----->|     */
/*                                                                                   */
/*-----------------------------------------------------------------------------------*/
typedef struct {
    L2ETH_BUFFER_DISCRIPTOR bd;
    L2ETH_UINT32 cur_pos;       /* this variable may be removed. */
    L2ETH_UINT32 avail_flag_array_size; /* no of elements of the avail flag array */
    L2ETH_PACKET *pPacketBlock; /* pointer to the packet block */
    L2ETH_UINT32 avail_flag[1];  /* bit-wise - 0=free, 1=in use */
} L2ETH_BUFFER_CONFIG;

typedef L2ETH_BUFFER_CONFIG *L2ETH_BUFFER_HANDLE;

/****INTERFACES TO BE EXPOSED****/
/*
Function to initialize the buffers.
The caller should allocate the memory and pass it to the buffer,
this function will only divide that allocated memory into split buffers
*/
EXTERN L2ETH_BUF_ERROR l2_buf_init(L2ETH_BUFFER_DISCRIPTOR buf_disc,    /* [in] */
    L2ETH_UINT32 prealloc_cnt,  /* [in] */
    L2ETH_BUFFER_CONFIG ** hBuf  /* [out] */
    );


/*
Function to remove the buffer management, associated with the buffers.
It's the callers responsibility free the memory
*/
EXTERN L2ETH_BUF_ERROR l2_buf_remove(L2ETH_BUFFER_HANDLE *hBuf /* [in] */ );

/*
Function to get the next free buffer
*/
EXTERN L2ETH_BUF_ERROR l2_buf_get_next(L2ETH_BUFFER_HANDLE hBuf,        /* [in] */
    L2ETH_PACKET ** pNext       /* [out] */
    );
/*
Function to free buffer
*/
EXTERN L2ETH_BUF_ERROR l2_buf_free(L2ETH_BUFFER_HANDLE hBuf,    /* [in] */
    L2ETH_PACKET * pNext        /* [in] */
    );

/*
Function to retrieve associated param of a given buffer
*/
L2ETH_BUF_ERROR l2_buf_get_packet(L2ETH_BUFFER_HANDLE hBuf,     /* [in] */
    L2ETH_UINT8 * pBuf,         /* [in] */
    L2ETH_PACKET ** ppPacket    /* [out] */
    );

/*
Function returns the number of free buffers in the buffer-ring
*/
EXTERN L2ETH_UINT32 l2_buf_get_free_cnt(L2ETH_BUFFER_HANDLE hBuf, /* [in] */
    L2ETH_UINT32 bits_cnt  /* [in] */
    );

/*
Function returns the number of total buffers in the buffer-ring
*/
EXTERN L2ETH_UINT32 l2_buf_get_total_cnt(L2ETH_BUFFER_HANDLE hBuf /* [in] */ );


#endif /* _L2ETH_BUF_MGMT_H */

