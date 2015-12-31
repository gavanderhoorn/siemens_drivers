/*****************************************************************************/
/* Copyright (C) SIEMENS CORP., 2015 All rights reserved.*/
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


#ifndef _TRACE_SUB_H_
#define _TRACE_SUB_H_

#define GET_GR_SNAME(subsys) subsys##_NAME

/* trace groups */
#define GR_INIT                 0x00000001      /* interface initialisation functions */
#define GR_INIT_NAME            "[INIT]"

#define GR_STATE                0x00000002      /* change state functions */
#define GR_STATE_NAME           "[STATE]"

#define GR_IO                   0x00000004      /* cyclic io-data function */
#define GR_IO_NAME              "[IO]"

#define GR_DS                   0x00000008      /* acyclic data function */
#define GR_DS_NAME              "[DS]"

#define GR_ALARM                0x00000010      /* alarm function */
#define GR_ALARM_NAME           "[ALARM]"

#define GR_MGT                  0x00000020      /* managment functions */
#define GR_MGT_NAME             "[MGT]"

#define GR_CHNL                 0x00000040      /* transport channel functions */
#define GR_CHNL_NAME            "[CHNL]"

#define GR_RT                   0x00000080      /* rt channel funktions */
#define GR_RT_NAME              "[RT]"

#define GR_IOR                  0x00000100      /* io router, concentrator, wdg funktions */
#define GR_IOR_NAME             "[IOR]"

#define GR_PE                   0x00000200      /* PE: PROFIenergy    */
#define GR_PE_NAME              "[PE]"

#define GR_FL                   0x00000400      /* flash operations   */
#define GR_FL_NAME              "[FL]"

#define GR_DR                   0x00000800      /* communication with driver */
#define GR_DR_NAME              "[DR]"

#endif /* _TRACE_SUB_H_ */

