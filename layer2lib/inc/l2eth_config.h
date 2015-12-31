/*****************************************************************************/
/*                                                                           */
/*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.*/
/*                                                                           */
/*    file: l2eth_config.h													                         */
/*                                                                           */
/*    Description:                                                           */
/*    l2 configuration declarations											                     */
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


#ifndef L2ETH_CONFIG_H
#define L2ETH_CONFIG_H

/* only hw constants */

/* maximum recieve buffer frame count */
#define MAX_ETHERNET_RECEIVE_FRAME_COUNT 40     //60


/* maximum send buffer pool frame count */
#define MAX_ETHERNET_SEND_FRAME_COUNT 40       //60

/* max of l2 packet frame size is */
#define MAX_ETHERNET_FRAME_SIZE 1520
#define MIN_ETHERNET_FRAME_SIZE 64	/* Data(46) + Ethernet Head(14) + Vlan tag(4) */

/* limits of l2 packet size */
#define MAX_L2_FRAME_SIZE 1518
#define MIN_L2_FRAME_SIZE 60

/* max CPs Supported */
#define MAX_CP_SUPPORTED (8)


#endif /* L2ETH_CONFIG_H */
