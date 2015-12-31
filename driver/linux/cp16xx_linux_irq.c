/*****************************************************************************/
/*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.*/
/*****************************************************************************/
/* FILE NAME    : cp16xx_linux_irq.c
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
/*****************************************************************************/

#include "../cp16xx_base.h"    /* common (kernel side only) structures and defines */

/* IRQ related functions(OS dependent)

   cp16xx_irq_shared_cbf - ISR

   cp16xx_os_irq_init - install and connect ISR

   cp16xx_os_irq_uninit - disconnect and remove ISR */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,19)
static irqreturn_t cp16xx_irq_shared_cbf(int irq, void *dev_id, struct pt_regs *regs)
#else
static irqreturn_t cp16xx_irq_shared_cbf(int irq, void *dev_id)
#endif
{
    u32 irtIrq, rtIrq, irq_handled = 0;
    struct cp16xx_card_data *card = (struct cp16xx_card_data *)dev_id;
    DPR_SPINLOCK_FLAGS flags;

    DPR_SPINLOCK_LOCK(card->smplock, flags);

    irtIrq = DPR_READ_UINT32(card->bars[PCI_BAR_IRTE].bar_ptr + HP_IRQ1_IRT);
    if(irtIrq) {
        #ifdef DBG_COUNTERS
            card->irt_irq_count++;
        #endif /* DBG_COUNTERS */
        ++irq_handled;

        /* clear the interrupting bit */
        DPR_WRITE_UINT32(irtIrq, card->bars[PCI_BAR_IRTE].bar_ptr + HP_IRQ_ACK_IRT);
    }

    rtIrq = DPR_READ_UINT32(card->bars[PCI_BAR_IRTE].bar_ptr + HP_IRQ1_RT);
    if(rtIrq) {
        #ifdef DBG_COUNTERS
            card->rt_irq_count++;
        #endif /* DBG_COUNTERS */
        ++irq_handled;

        /* clear the interrupting bit */
        DPR_WRITE_UINT32(rtIrq, card->bars[PCI_BAR_IRTE].bar_ptr + HP_IRQ_ACK_RT);
    }

    /* signal end of irq, propably spurios interrupt from ERTEC */
    DPR_WRITE_UINT32(0x0000000F, card->bars[PCI_BAR_IRTE].bar_ptr + HP_EOI_IRQ1);

    DPR_SPINLOCK_UNLOCK(card->smplock, flags);

    if(irtIrq) {
        if(irtIrq & OPFAULT_BITS)
            card->opfaultfct(card);

        if(irtIrq & BIT_IRQ_STARTOP)
            card->startopfct(card);

        if(irtIrq & BIT_IRQ_NEWCYCLE) {
            #ifdef DBG_COUNTERS
                card->newcyc_irq_count++;
            #endif /* DBG_COUNTERS */
            card->newcyclefct(card);
        }
    }
    if(rtIrq) {
        DPR_WAKEUP_QUEUE(card->rt_irq);
        dprlib_int_callback(&card->cp);
    }

    if(irq_handled) {
        return IRQ_HANDLED;
    } else {
        return IRQ_NONE;
    }
}

int cp16xx_os_irq_init(struct cp16xx_card_data *card)
{
    int err = -EFAULT;
    DPRLIBLOGMSG("begin\n");

    DPRLIBLOGMSG("request irq %i, card 0x%p\n", card->os_info.irq, card);
    if(card->os_info.irq >= 0) {
        if((err = request_irq(card->os_info.irq, cp16xx_irq_shared_cbf,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,22)
            SA_SHIRQ | SA_INTERRUPT,
#else
            IRQF_SHARED,
#endif
            "cp16xx", card))) {

            DPRLIBERRMSG("can't get assigned irq %i, error %i\n", card->os_info.irq, err);
            return err;
        }
        DPRLIBLOGMSG("request irq %i  -> OK\n", card->os_info.irq);
    }

  #ifdef DBG_COUNTERS
    card->newcyc_irq_count = 0;
    card->rt_irq_count = 0;
    card->irt_irq_count = 0;
  #endif /* DBG_COUNTERS */

    cp16xx_irq_set_mode(card);
    cp16xx_irq_restore_mask_rt(card);
    cp16xx_irq_restore_mask_irt(card);

    DPRLIBLOGMSG("end\n");

    return 0;
}

void cp16xx_os_irq_uninit(struct cp16xx_card_data *card)
{
    DPRLIBLOGMSG("begin\n");

    cp16xx_irq_reset_mask_irt(card);
    cp16xx_irq_reset_mask_rt(card);

    if(card->os_info.irq >= 0) {
        free_irq(card->os_info.irq, card);
    }

    DPRLIBLOGMSG("end\n");
}

static ssize_t cp16xx_os_syncronize_irt(struct cp16xx_interface *interface, size_t count)
{
    int ret = 0;
    DPR_WAIT_POINT wait;
    DPRLIBLOGMSG("begin\n");

    DPR_PREPARE_WAIT_ON_POINT(wait);
    if(count == CP16XX_STARTOP) {
        DPR_WAIT_ON_POINT(interface->card->startop_irq, wait);
    } else if(count == CP16XX_OPFAULT) {
        DPR_WAIT_ON_POINT(interface->card->opfault_irq, wait);
    } else if(count == CP16XX_NEWCYCLE) {
        DPR_WAIT_ON_POINT(interface->card->newcycle_irq, wait);
    }

    schedule();

    if(count == CP16XX_STARTOP) {
        DPR_REMOVE_WAIT_POINT(interface->card->startop_irq, wait);
    } else if(count == CP16XX_OPFAULT) {
        DPR_REMOVE_WAIT_POINT(interface->card->opfault_irq, wait);
    } else if(count == CP16XX_NEWCYCLE) {
        DPR_REMOVE_WAIT_POINT(interface->card->newcycle_irq, wait);
    }

    DPRLIBLOGMSG("end\n");

    return ret;
}
