/*****************************************************************************
*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.
*
* FILE NAME    : krtlb_common.c
*
* DESCRIPTION  : KRAM IO table module.
******************************************************************************/

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


#define NOTRC
#include "kramiotlb.h"

/* host/target functions */

void KRAMIOTLB_init(
    void          *p_iotlb,   /* in, beginning of the io table */
    unsigned long  iotlb_len, /* in, length reserved for io table */
    KRAMIOTLB_Header *header) /* "header" is the controll structure, 
                                 that will be initialized in this function,
                                 you need "header" everytime, to use KRAMIOTLB_... functions */
{
    KTLB_TRC_2("init p_iotlb=%p iotlb_len=%lu", p_iotlb, iotlb_len);

    /* at the beginn of the KRAMIOTLB-Buffer is the currently maximum occupied position
       after that follow KRAMIOTLB_Item(s) */

    header->pMaxItemPos = (PNIO_UINT32 *)p_iotlb;

    /* after MaxItemPos is array of KRAMIOTLB_Item(s) */
    /* header->pFirstItem is the pointer to first array item */
    header->pFirstItem = (KRAMIOTLB_Item *)( (unsigned char*)p_iotlb + sizeof(*(header->pMaxItemPos)));

    /* the array size is = (iotlb_len - sizeof(MaxItemPos))/ sizeof(KRAMIOTLB_Item) - 1 */
    /* header->pLastItem is the pointer to last possible array item */
    header->pLastItem = &header->pFirstItem[ (iotlb_len - 
                                              sizeof(*(header->pMaxItemPos)))/ sizeof(KRAMIOTLB_Item) - 1];
}

void KRAMIOTLB_deinit(
    KRAMIOTLB_Header *header)
{
}

KRAMIOTLB_Ret KRAMIOTLB_GetHandleItems(
    PNIO_UINT32 hnd,
    PNIO_UINT32 min_data_length, /* in, use 1 if you don't need diagnostic addresses */
    PNIO_UINT32 *items_count, /* in,out */
    KRAMIOTLB_Item **p_item,  /* out */
    const KRAMIOTLB_Header *header) /* in */
{
    unsigned long RealNumber = 0;
    KRAMIOTLB_Item *pTmpItem, *pCurMaxItem = &header->pFirstItem[SWAP_D(*header->pMaxItemPos)];
    KRAMIOTLB_Ret ret = KRAMIOTLB_OK;

    if(!items_count)
      return KRAMIOTLB_ERR_PRM;

    for (pTmpItem = header->pFirstItem;
         pTmpItem <= pCurMaxItem;
         pTmpItem++) {
        if (SWAP_D(pTmpItem->iotlb_hndl) == hnd &&
            SWAP_D(pTmpItem->used) == 1 &&
            SWAP_D(pTmpItem->data_length) >= min_data_length) {
            RealNumber++;
            if (p_item && *items_count > (RealNumber -1)) {
                *p_item = pTmpItem;
                (p_item)++;
            }
        }
    }

    *items_count = RealNumber;
    KTLB_TRC_2("get handle items hnd=0x%08x real_items_cnt=%ld", hnd, RealNumber);

    return ret;
}

KRAMIOTLB_Ret KRAMIOTLB_GetHandleItemsAdvance(
        PNIO_UINT32           hnd,         /* wicht muss be equal to iotlb_hndl from KRAMIOTLB_Item */
        PNIO_UINT32           min_data_length, /* in, use 1 if you don't need diagnostic addresses */
        PNIO_UINT32         * items_count, /* in,out */
        KRAMIOTLB_Item     ** p_item,      /* out */
        KRAMIOTLB_Item      * p_addition_cmp_list,   /* in, optional, default 0 */
        PNIO_UINT32           addition_cmp_list_len, /* in, optional, default 0 */
        KRAMIOTLB_IsItemValid p_fct_is_item_valid,  /* in, optional, default 0 */
        const KRAMIOTLB_Header    * kramHdr) /* in */
{
    unsigned long RealNumber = 0;
    KRAMIOTLB_Item *pTmpItem, *pCurMaxItem = &kramHdr->pFirstItem[SWAP_D(*kramHdr->pMaxItemPos)];
    KRAMIOTLB_Ret ret = KRAMIOTLB_OK;

    if(!items_count)
      return KRAMIOTLB_ERR_PRM;

    for (pTmpItem = kramHdr->pFirstItem;
         pTmpItem <= pCurMaxItem;
         pTmpItem++) {

        if (SWAP_D(pTmpItem->iotlb_hndl) == hnd &&
            SWAP_D(pTmpItem->used) == 1 &&
            SWAP_D(pTmpItem->data_length) >= min_data_length &&

            (p_fct_is_item_valid == 0 || /* no function, no validation */
              p_fct_is_item_valid(pTmpItem, p_addition_cmp_list, addition_cmp_list_len)) )
        {
            RealNumber++;
            if (p_item && *items_count > (RealNumber -1)) {
                /*printf("KRAMIOTLB_GetHandleItemsAdvance adds addr=%u in_out=%u\n",
                 pTmpItem->log_addr, pTmpItem->io_out_type);*/
                *p_item = pTmpItem;
                (p_item)++;
            }
        }
    }

    *items_count = RealNumber;
    KTLB_TRC_2("get handle items hnd=0x%08x real_items_cnt=%ld", hnd, RealNumber);

    return ret;
}


/**
 * This humpling function caused a bunch of ARTS-Requests!!
 *
 * Depending on p_item and *items_count the function has *TWO* different use cases:
 * 1) (p_item == NULL)  || (*items_count == 0)
 *    Counts elements:
 *      --> does *NOT* fill up your ** p_item - array
 *      --> only returns count of found elements in *items_count;
 *
 * 2) (p_item != NULL) ||  (*items_count != 0)
 *    Counts elements and returns references of elements:
 *    --> copies pointers of found elements into ** p_item - array
 *    --> returns count of found elements in *items_count;
 */

KRAMIOTLB_Ret KRAMIOTLB_GetHandleDeviceItems(
        PNIO_UINT32           hnd,
        PNIO_UINT32           device_nr,
        KRAMIOTLB_IN_OUT_TYPE io_type,     /* in */
        PNIO_UINT32         * items_count,  /* in,out */
        KRAMIOTLB_Item     ** p_item,       /* out */
        const KRAMIOTLB_Header    * kramHdr)      /* in */
{
  unsigned long RealNumber = 0;
  KRAMIOTLB_Item *pTmpItem, *pCurMaxItem = &kramHdr->pFirstItem[SWAP_D(*kramHdr->pMaxItemPos)];
  KRAMIOTLB_Ret ret = KRAMIOTLB_OK;

  if(!items_count)
    return KRAMIOTLB_ERR_PRM;


  for (pTmpItem = kramHdr->pFirstItem;
       pTmpItem <= pCurMaxItem;
       pTmpItem++) {
      if (SWAP_D(pTmpItem->iotlb_hndl) == hnd &&
          SWAP_D(pTmpItem->used) == 1 &&
          SWAP_D(pTmpItem->device_ar) == device_nr &&
          (KRAMIOTLB_IN_OUT_TYPE)SWAP_D(pTmpItem->io_out_type) & io_type) {
          RealNumber++;
          if (p_item && *items_count > (RealNumber -1)) {
              *p_item = pTmpItem;
              (p_item)++;
          }
      }
  }

  *items_count = RealNumber;
  KTLB_TRC_2("KRAMIOTLB_GetHandleDeviceItems hnd=0x%08x real_items_cnt=%ld", hnd, RealNumber);

  return ret;
}

KRAMIOTLB_Ret KRAMIOTLB_GetDataOffset(
        PNIO_UINT32           hnd,         /* in, user, application handle */
        KRAMIOTLB_IN_OUT_TYPE io_type,     /* in */
        KRAMIOTLB_IOSYNC_TYPE sync_type,   /* in */
        PNIO_UINT32         * min_data_offset, /* out */
        PNIO_UINT32         * max_data_offset, /* out */
        const KRAMIOTLB_Header    * kramHdr)   /* in */
{
  KRAMIOTLB_Item *pTmpItem, *pCurMaxItem = &kramHdr->pFirstItem[SWAP_D(*kramHdr->pMaxItemPos)];

  *min_data_offset = 0xFFFFFFFF;
  *max_data_offset = 0;

  for (pTmpItem = kramHdr->pFirstItem;
        pTmpItem <= pCurMaxItem;
         pTmpItem++) {
      if (SWAP_D(pTmpItem->iotlb_hndl) == hnd &&
           SWAP_D(pTmpItem->used) == 1 &&
           (KRAMIOTLB_IOSYNC_TYPE)SWAP_D(pTmpItem->io_sync_type) == sync_type &&
            SWAP_D(pTmpItem->data_length) > 0 ){

          if(SWAP_D(pTmpItem->io_out_type) & io_type) {
            /* allow for data */
            if( SWAP_D(pTmpItem->data_length) + SWAP_D(pTmpItem->iops_length) > 0)
            {
              if( SWAP_D(pTmpItem->data_offset) < *min_data_offset) {
                *min_data_offset = SWAP_D(pTmpItem->data_offset);
              }

              if((SWAP_D(pTmpItem->data_offset) + SWAP_D(pTmpItem->data_length) +
                      SWAP_D(pTmpItem->iops_length)) > *max_data_offset) {
                *max_data_offset = SWAP_D(pTmpItem->data_offset) +
                                    SWAP_D(pTmpItem->data_length) +
                                     SWAP_D(pTmpItem->iops_length);
              }
            }
          }
          else{
            /* allow for stutus */
            if(SWAP_D(pTmpItem->iocs_length) > 0)
            {
              if(SWAP_D(pTmpItem->iocs_offset) < *min_data_offset){
                *min_data_offset = SWAP_D(pTmpItem->iocs_offset);
              }

              if((SWAP_D(pTmpItem->iocs_offset) + SWAP_D(pTmpItem->iocs_length)) >
                                     *max_data_offset) {
                *max_data_offset = SWAP_D(pTmpItem->iocs_offset) +
                                    SWAP_D(pTmpItem->iocs_length);
              }
            }
          }

          /*printf("GetDataOffset in-out s%d ss%d %x d_o %x d_l %x cs_o %x cs_l %x\n",
                 pTmpItem->slot_nr, pTmpItem->subslot_nr,
								  pTmpItem->io_out_type, pTmpItem->data_offset, pTmpItem->data_length,
                   pTmpItem->iocs_offset, pTmpItem->iocs_length);
          printf("GetDataOffset min %x max %x\n\n", *min_data_offset, *max_data_offset);*/
      }
  }

  if(*min_data_offset == 0xFFFFFFFF){
    *min_data_offset = 0;
  }

  return KRAMIOTLB_OK;
}

KRAMIOTLB_Ret KRAMIOTLB_IsIoSyncConfigured(
        PNIO_UINT32           hnd,         /* in, user, application handle */
        KRAMIOTLB_IOSYNC_TYPE sync_type,   /* in */
        PNIO_UINT8          * configured,  /* out, 0 - no, 1 - yes */
        const KRAMIOTLB_Header    * kramHdr) /* in */
{
  KRAMIOTLB_Item *pTmpItem, *pCurMaxItem = &kramHdr->pFirstItem[SWAP_D(*kramHdr->pMaxItemPos)];
  *configured = 0;

  if (NULL != kramHdr->pFirstItem) {
    for (pTmpItem = kramHdr->pFirstItem;
         pTmpItem <= pCurMaxItem;
         pTmpItem++) {
        if (SWAP_D(pTmpItem->iotlb_hndl) == hnd &&
            SWAP_D(pTmpItem->used) == 1 &&
            (KRAMIOTLB_IOSYNC_TYPE)SWAP_D(pTmpItem->io_sync_type) == sync_type) {
            *configured = 1;
            break;
        }
    }
  }
  return KRAMIOTLB_OK;
}

KRAMIOTLB_Ret KRAMIOTLB_FindItemByGeoAddr(
        PNIO_UINT32           hnd,       /* in, iobase instance */
        PNIO_UINT32           slot_nr,   /* in */
        PNIO_UINT32           subslot_nr,/* in */
        KRAMIOTLB_IN_OUT_TYPE inout_type,   /* in */
        KRAMIOTLB_Item     ** p_item,    /* out */
        const KRAMIOTLB_Header    * kramHdr)
{
  KRAMIOTLB_Item *pTmpItem, *pCurMaxItem = &kramHdr->pFirstItem[SWAP_D(*kramHdr->pMaxItemPos)];

  *p_item = NULL;

  for (pTmpItem = kramHdr->pFirstItem;
       pTmpItem <= pCurMaxItem;
       pTmpItem++) {
      if (SWAP_D(pTmpItem->iotlb_hndl) == hnd &&
          SWAP_D(pTmpItem->used) == 1 &&
          SWAP_D(pTmpItem->slot_nr) == slot_nr &&
          SWAP_D(pTmpItem->subslot_nr) == subslot_nr &&
          SWAP_D(pTmpItem->io_out_type) & inout_type){
              *p_item = pTmpItem;
              return KRAMIOTLB_OK;
      }

  }

  KTLB_TRC_2("KRAMIOTLB_FindItemByGeoAddr slot:%i subslot:%i not found", slot_nr, subslot_nr);

  return KRAMIOTLB_ERR_ADDR;
}
