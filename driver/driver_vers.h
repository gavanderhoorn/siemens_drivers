/*****************************************************************************/
/*   Copyright (C) SIEMENS CORP., 2015 All rights reserved.*/
/*****************************************************************************/
/*  F i l e               driver_vers.h                                      */
/*****************************************************************************/
/*  D e s c r i p t i o n:  Common header declarations                       */
/*                          This is common to Linux and vxWorks !!!          */
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

/*                                                                           */
/*   Description  : Defines version number and describes the version history.*/
/*                                                                           */
/*   History      : All changes have to be documented below in this file.    */
/*   ========       Note: Do NOT use leading 0 in the version numbers.       */
/*                  E.g.: 08 is interpreted as octal and cause an error!!!   */
/*                                                                           */
/*****************************************************************************/

#ifndef _DRIVER_VERS_H_
#define _DRIVER_VERS_H_

/* driver version: The full driver version number is e.g.: '1.2.3.4'
 *                 First 2 digits are the CD firmware + host sw version,
 *                 third digit is a driver version defined here,
 *                 fourth digit is a build number defined by the build process.
 * IMPORTANT NOTE: Because of dependencies with the firmware, we build the driver
 *                 every time the FW is generated. Therefor we are using the same
 *                 minor version number. The build number is always incremented.
 *                 Increment DRV_VER_MINOR manualy only if driver must be changed
 *                 without a new firmware build.
 *                 See also: \firmware\inc\fw1616dk_vers.h, fw_vers_bldnum.h
 */
#define DRV_VER_MINOR    FW_VER_MINOR2

/* #define DRV_VER_MINOR    xxx        */


/* version description begin:  (current first, oldest last)

V1.1.4.x: PL: 04.08.2005 - Firmware version string update: Last digit is now a build number which is
                           'x' == Build number in the version string was added.
      0 : PL: 03.08.2005 - 1st Host-Linux + Firmware same CS version.

----- version description end -----
*/


#endif /* _DRIVER_VERS_H_ */

