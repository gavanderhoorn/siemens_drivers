/****************************************************************************/
/*                                                                          */
/*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.*/
/*                                                                          */
/*    file: l2eth_errs.h                                                    */
/*                                                                          */
/*    Description:                                                          */
/*    error codes for IO-Base user interface                                */
/*                                                                          */
/****************************************************************************/
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

#ifndef _L2ETH_ERRS_H
#define _L2ETH_ERRS_H

/****************************************************************************/
/* IMPORTANT                                                                */
/* All the errors which are specific to firmware should have values between */
/* 0-255 because, the error field is only 1 byte for the communication betn */
/* L2 agent and L2 host.                                                    */
/****************************************************************************/

#define L2ETH_OK                            0x00  /* success */

/****************************************************************************/
/* F I R M W A R E   S P E C I F I C   E R R O R S                          */
/****************************************************************************/
#define L2ETH_ERR_PRM_HND                   0x01  /* parameter Handle is illegal */
#define L2ETH_ERR_PRM_BUF                   0x02  /* The buffer pointer or buffer contents are invalid */
#define L2ETH_ERR_PRM_LEN                   0x03  /* parameter length is wrong */
#define L2ETH_ERR_PRM_QUERY                 0x04  /* parameter query is invalid */
#define L2ETH_ERR_PRM_OID                   0x05  /* parameter oid is invalid */
#define L2ETH_ERR_OID_READONLY              0x06  /* the oid cannot be written */
#define L2ETH_ERR_CANCEL_RQB                0x07  /* requested RQB to FW is cancelled, returning unused RQB to Host */
#define L2ETH_ERR_DELIVERY                  0x08  /* requested message could not be delivered to FW. Host should reattempt sending the same thr DPR */
#define L2ETH_ERR_SEQUENCE                  0x09  /* wrong calling sequence */
#define L2ETH_ERR_MAX_REACHED               0x0A  /* maximal number of opens reached; close unused applications */
#define L2ETH_ERR_NO_RESOURCE               0x0B  /* no resouce too many requests been processed */

#define L2ETH_ERR_INTERNAL                  0xFF  /* fatal error, contact SIEMENS hotline */

/****************************************************************************/
/* H O S T   S P E C I F I C   E R R O R S                                  */
/****************************************************************************/

#ifndef _L2AG_FIRMWARE
/* THE FW SHOULD USE ONLY FW SPECIFIC ERRORS,
   THE HOST CAN USE BOTH HOST AND FW SPECIFIC ERRORS */

#define L2ETH_ERR_PRM_PCBF                  0x101  /* parameter cbf is illegal */
#define L2ETH_ERR_PRM_TYPE                  0x102  /* parameter type has no valid value */
#define L2ETH_ERR_PRM_CP_ID                 0x103  /* parameter CpIndex is wrong - out of allowed range */
#define L2ETH_ERR_PRM_TIMEOUT               0x104  /* parameter timeout has no valid value */
#define L2ETH_ERR_PRM_MODE                  0x105  /* parameter mode is invalid */
#define L2ETH_ERR_PRM_PKT                   0x106  /* parameter packet pointer is invalid */
#define L2ETH_ERR_LLDP_FRAME                0x107  /* trying to send lldp frame */

/* other errors */
#define L2ETH_ERR_NO_CONNECTION             0x301  /* L2Interface data not available, because L2Interface is not                                                                                                connected to controller */
#define L2ETH_ERR_NO_LIC_SERVER             0x302  /* licence server not running, check your installation  */
#define L2ETH_ERR_NO_FW_COMMUNICATION       0x303  /* no communication with firmware, propably driver is not
                                                      loaded, card is not found with cpid provided
                                                      or make sure firmware runs, if not reset cp */

#endif /* _L2AG_FIRMWARE */

#endif  /* _L2ETH_ERRS_H */

