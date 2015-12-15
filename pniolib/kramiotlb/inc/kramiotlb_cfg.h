/*****************************************************************************/
/* DESCRIPTION: configuration file for KRAMIOTLB interface                   */
/* DATE:        29.11.2015                                                   */
/*                                                                           */
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


#ifndef KRAMIOTLB_CFG_H
#define KRAMIOTLB_CFG_H

#include "os.h"
#include "pniobase.h"

#define SWAP_W(var) CPU_TO_LE16(var)
#define SWAP_D(var) CPU_TO_LE(var)
#define CNS_SWAP_32(var) CPU_TO_LE(var)

/* trace macros only for test */
/* #define KTLB_TRC_ON */
#ifdef  KTLB_TRC_ON
#include "stdio.h"              /* wegen KTLB_TRC_X */
#define KTLB_TRC_0(s)        printf("KRAMIOTLB(%s): "s"\n", __FUNCTION__)
#define KTLB_TRC_1(s,p1)     printf("KRAMIOTLB(%s): "s"\n", __FUNCTION__, p1)
#define KTLB_TRC_2(s,p1,p2)  printf("KRAMIOTLB(%s): "s"\n", __FUNCTION__, p1, p2)
#else
#define KTLB_TRC_0(s)
#define KTLB_TRC_1(s,p1)
#define KTLB_TRC_2(s,p1,p2)
#endif

/* #define IODU_ENABLE_MULTIUSER_LOCKING */
#ifndef __sparc__ /* FIXME */
#define IODU_ENABLE_INTERPROCESS_LOCKING
#endif

/* define, to use KRAMIOTLB_AddItem, KRAMIOTLB_FreeItems */
/* #define KRAMIOTLB_SUPPORT_TARGET */

/* define, to use KRAMIOTLB_GetContrItemByLogAddr */
#define KRAMIOTLB_SUPPORT_HOST_CONTROLLER

#define KRAMIOTLB_SUPPORT_HOST_CONTROLLER_HASH

/* define, to use KRAMIOTLB_CreateContrHash, KRAMIOTLB_FreeContrHash */
#define KRAMIOTLB_SUPPORT_HOST_CONTROLLER_HASH_SORT

/* define, to use  IODU_ctrl_data_read_ex, IODU_ctrl_data_write_ex */
#define IODU_SUPPORT_IO_CACHE_CONTROLLER

/* define, to use KRAMIOTLB_GetDeviceItems */
#define KRAMIOTLB_SUPPORT_HOST_DEVICE

/* build for host software */
#define KRAMIOTLB_HOST

#define IODU_ERTEC_TYPE IODU_ERTEC400

#endif /* KRAMIOTLB_CFG_H */
