/*****************************************************************************/
/*   Copyright (C) SIEMENS CORP., 2015 All rights reserved.*/
/*****************************************************************************/
/*  F i l e               pniolib_vers.h                                     */
/*****************************************************************************/
/*  D e s c r i p t i o n:  Version header                                   */
/*                          Is used in the version resource file: *.rc       */
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
/*****************************************************************************/
#ifndef _PNIOLIB_VERS_INCD_
#define _PNIOLIB_VERS_INCD_



/* use global product number  (use CP16xx CD style) */

/* CP1616DK vers: */

#include "siemens.h"
#include "fw1616dk_vers.h"  /* fw version constant FW_VER_MAJOR, FW_VER_MINOR1... */
                               /* and fw_vers_bldnum.h: VERSION_BUILD_NUMBER, VERSION_BUILD_INCREMENT    */
#include "version_variant.h"
#define SINEC_DRV_MAJOR   FW_VER_MAJOR
#define SINEC_DRV_MINOR   FW_VER_MINOR1
#define SINEC_DRV_VARIANT FW_VER_MINOR2   /*  MY_PNIOLIB_VER_VARIANT not used, replaced by _MINOR2 == HotFix */
#define SINEC_DRV_BUILD   VERSION_BUILD_NUMBER

/* stringizing macros */
#ifndef chSTR
#define chSTR(x)  #x
#define chSTR2(x) chSTR(x)
#endif /* chSTR */
#define chSTR3(x) "0" chSTR(x)


#ifdef _DEBUG
#define DEBREL "-DBG"
#else
#define DEBREL "-REL"
#endif

#ifdef _LOCAL_GEN
#define PROVER "L "
#define X_BLD  " "               /* SpecialBuild string extension (not used yet)*/
#else
#define PROVER "V "
#define X_BLD  " "               /* empty */
#endif

/* Convert version numbers to zero prefixed version strings */
#if FW_VER_MAJOR < 10
#define FW_VER_MAJOR_2D chSTR3(FW_VER_MAJOR)
#else
#define FW_VER_MAJOR_2D chSTR2(FW_VER_MAJOR)
#endif

#if FW_VER_MINOR1 < 10
#define FW_VER_MINOR1_2D chSTR3(FW_VER_MINOR1)
#else
#define FW_VER_MINOR1_2D chSTR2(FW_VER_MINOR1)
#endif

#if FW_VER_MINOR2 < 10
#define FW_VER_MINOR2_2D chSTR3(FW_VER_MINOR2)
#else
#define FW_VER_MINOR2_2D chSTR2(FW_VER_MINOR2)
#endif

#if FW_VER_MINOR3 < 10
#define FW_VER_MINOR3_2D chSTR3(FW_VER_MINOR3)
#else
#define FW_VER_MINOR3_2D chSTR2(FW_VER_MINOR3)
#endif

#define MY_FILE_VERSION      SINEC_DRV_MAJOR,SINEC_DRV_MINOR,SINEC_DRV_VARIANT,SINEC_DRV_BUILD
#define MY_FILE_VERSION_STR  "V " chSTR2(SINEC_DRV_MAJOR) "." chSTR2(SINEC_DRV_MINOR) \
                             "." chSTR2(SINEC_DRV_VARIANT) "."  \
                             chSTR2(SINEC_DRV_BUILD) DEBREL

/* substitution for prod.h: */
#define VER_PRODUCTVERSION      SINEC_DRV_MAJOR,SINEC_DRV_MINOR,SINEC_DRV_VARIANT
#define VER_PRODUCTVERSION_STR "V " chSTR2(SINEC_DRV_MAJOR) "." chSTR2(SINEC_DRV_MINOR) \
                               "." chSTR2(SINEC_DRV_VARIANT)

#define MY_COMMENTS_STR           "servlib\0"
#define MY_FILE_DESCRIPTION_STR   "servlib\0"
#define MY_INTERNAL_NAME          "servlib\0"
#define MY_ORIGINAL_FILENAME      "servlib.dll\0"
#define MY_PRIVATE_BUILD_STR      "servlib" DEBREL " \0"
#define MY_SPECIAL_BUILD_STR      "servlib" DEBREL X_BLD " \0"

#endif /* _PNIOLIB_VERS_INCD_ */

