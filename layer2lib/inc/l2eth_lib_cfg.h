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
/*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.*/
/*    file: l2eth_lib_cfg.h                                                  */
/*    Description:                                                           */
/*    os abstraction for l2library                                           */
/*****************************************************************************/
/*****************************************************************************/

#ifndef L2ETH_LIB_CFG_H
#define L2ETH_LIB_CFG_H

typedef DPR_DRV_HANDLE L2ETH_DRV_HANDLE;
#define L2ETH_DRV_OPEN DPR_DRV_OPEN
#define L2ETH_DRV_CLOSE DPR_DRV_CLOSE
#define L2ETH_DRV_WRITE DPR_DRV_WRITE
#define L2ETH_DRV_READ DPR_DRV_READ
#define L2ETH_DRV_ERROR DPR_DRV_ERROR
#define L2ETH_DRV_IOCTL DPR_DRV_IOCTL
#define L2ETH_DRV_MMAP DPR_DRV_MMAP
#define L2ETH_DRV_MUNMAP DPR_DRV_MUNMAP

#define L2ETH_STRERROR DPR_STRERROR


typedef DPR_MUTEX L2ETH_MUTEX;
#define L2ETH_MUTEX_CREATE_UNLOCKED(muxObj) DPR_MUTEX_CREATE_UNLOCKED(muxObj)
#define L2ETH_MUTEX_LOCK(muxObj) DPR_MUTEX_LOCK(muxObj)
#define L2ETH_MUTEX_UNLOCK(muxObj) DPR_MUTEX_UNLOCK(muxObj)
#define L2ETH_MUTEX_DESTROY(muxObj) DPR_MUTEX_DESTROY(muxObj)

typedef DPR_SEMAPHORE L2ETH_SEMAPHORE;
#define L2ETH_SEM_CREATE(semObj) DPR_SEM_CREATE(semObj)
#define L2ETH_SEM_WAIT_INTERRUPTIBLE(semObj) DPR_SEM_WAIT_INTERRUPTIBLE(semObj)
#define L2ETH_SEM_WAIT(semObj) DPR_SEM_WAIT(semObj)
#define L2ETH_SEM_POST(semObj) DPR_SEM_POST(semObj)
#define L2ETH_SEM_DESTROY(semObj) DPR_SEM_DESTROY(semObj)

typedef DPR_THREAD_HANDLE L2ETH_THREAD_HANDLE;
#define L2ETH_CALLBACK_DECL DPR_THREAD_DECL
#define L2ETH_THREAD_CREATE DPR_THREAD_CREATE
#define L2ETH_THREAD_JOIN(tHndl) DPR_THREAD_JOIN(tHndl)
#define L2ETH_THREAD_RETURN_TYPE DPR_THREAD_RETURN_TYPE
#define L2ETH_THREAD_END DPR_THREAD_END

#define L2ETH_VMALLOC DPR_VMALLOC
#define L2ETH_VFREE DPR_VFREE
#define L2ETH_ZALLOC DPR_ZALLOC
#define L2ETH_FREE DPR_FREE

#define L2ETH_DBG_ASSERT DPR_ASSERT

#endif /* #ifndef L2ETH_LIB_CFG_H */
