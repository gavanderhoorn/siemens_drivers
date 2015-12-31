/****************************************************************************
*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.
*****************************************************************************
* FILE NAME    : pnopping.c
* ---------------------------------------------------------------------------
* DESCRIPTION  : Test application
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
/*****************************************************************************/

#if defined(_DPR_WINDOWS)
	#include "windows.h"
	#include <stdio.h>
	#include <stdlib.h>
#elif defined(_DPR_LINUX)
    #include <stdio.h>
    #include <unistd.h>
    #include <stdlib.h>
#endif

#include "pnioerrx.h"
#include "pniousrx.h"
#include "pniousrt.h"

PNIO_UINT32 app_handle;
PNIO_UINT8 data[64];
PNIO_MODE_TYPE current_mode;

void mode_ind(PNIO_CBE_PRM * pCbfPrm)
{
    if(pCbfPrm->CbeType != PNIO_CBE_MODE_IND) {
        printf("invalid type of callback\n");
        return;
    }

    if(pCbfPrm->Handle != app_handle) {
        printf("invalid handle in callback\n");
        return;
    }

    current_mode = pCbfPrm->ModeInd.Mode;

}

void wait_for(PNIO_MODE_TYPE mode, unsigned long timeout_ms)
{
    unsigned long i;

    for(i = 0; i < timeout_ms; i++) {
        #if defined(_DPR_WINDOWS)
            Sleep(1);
        #else
            sleep(1);
        #endif
        if(mode == current_mode)
            return;
    }
}

void set_tile(PNIO_UINT8 *pBuffer, PNIO_UINT32 BufLen, PNIO_UINT8 start_value)
{
    PNIO_UINT32 i;
    for(i = 0; i < BufLen; i++, start_value++) {
        pBuffer[i] = start_value;
    }
}

int compare_tile(PNIO_UINT8 *pBuffer, PNIO_UINT32 BufLen, PNIO_UINT8 start_value)
{
    PNIO_UINT32 i;
    for(i = 0; i < BufLen; i++, start_value++) {
        if(pBuffer[i] != start_value)
            return 0;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    PNIO_UINT32 ret;
    unsigned int loops, i, start_value;

    /* default */
    loops = 10;
    start_value = 0;

    if(argc > 1) {
        sscanf(argv[1], "%u", &loops);
    }
    if(argc > 2) {
        sscanf(argv[2], "%u", &start_value);
    }

    fprintf(stdout, "PNIO_controller_open\n");
    ret = PNIO_controller_open(1, PNIO_CEP_MODE_CTRL, mode_ind, mode_ind, NULL, &app_handle);
    if(PNIO_OK != ret) {
        fprintf(stderr, "PNIO_controller_open failed %x\n", ret);
        exit(-1);
    }

    for(i = 0; i < loops; i++, start_value++) {
        /* set tile */
        set_tile(data, sizeof(data), start_value);

        fprintf(stdout, "PNIO_data_test loop %u\n", i);
        ret = PNIO_data_test(app_handle, data, sizeof(data));
        if(PNIO_OK != ret) {
            fprintf(stderr, "PNIO_data_test failed %x\n", ret);
        }

        /* compare */
        if(!compare_tile(data, sizeof(data), start_value))
            fprintf(stderr, "ERROR inconsistenz\n");
    }

    fprintf(stdout, "PNIO_close\n");
    PNIO_close(app_handle);
    fprintf(stdout, "success\n");
    return 0;
}
