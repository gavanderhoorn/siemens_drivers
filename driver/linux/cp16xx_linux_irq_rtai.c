/*****************************************************************************/
/*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.*/
/*****************************************************************************/
/* FILE NAME    : cp16xx_linux_irq_rtai.c
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

#ifdef RTAI

/* IRQ related functions(OS dependent)

   cp16xx_irq_shared_cbf - ISR

   cp16xx_irq_shared_cbf_rt - running for non RT services in secondar domain

   cp16xx_os_irq_init - install and connect ISR

   cp16xx_os_irq_uninit - disconnect and remove ISR */

static irqreturn_t cp16xx_irq_shared_cbf(int irq, void *dev_id, struct pt_regs *regs)
{
    u32 irtIrq, rtIrq, irq_handled = 0;
    struct cp16xx_card_data *card = (struct cp16xx_card_data *)dev_id;
    DPR_SPINLOCK_FLAGS flags;

    flags = rt_spin_lock_irqsave(&card->smplock);

    irtIrq = DPR_READ_UINT32(card->bars[PCI_BAR_IRTE].bar_ptr + HP_IRQ1_IRT);
    if(irtIrq) {
        ++irq_handled;

        if(irtIrq & OPFAULT_BITS)
            card->opfaultfct(card);

        if(irtIrq & BIT_IRQ_STARTOP)
            card->startopfct(card);

        if(irtIrq & BIT_IRQ_NEWCYCLE)
            card->newcyclefct(card);

        /* clear the interrupting bit */
        DPR_WRITE_UINT32(irtIrq, card->bars[PCI_BAR_IRTE].bar_ptr + HP_IRQ_ACK_IRT);
    }

    rtIrq = DPR_READ_UINT32(card->bars[PCI_BAR_IRTE].bar_ptr + HP_IRQ1_RT);
    if(rtIrq) {
        ++irq_handled;

        rt_pend_linux_irq(card->os_info.irq);

        /* clear the interrupting bit */
        DPR_WRITE_UINT32(rtIrq, card->bars[PCI_BAR_IRTE].bar_ptr + HP_IRQ_ACK_RT);
    }

    /* signal end of irq, propably spurios interrupt from ERTEC */
    DPR_WRITE_UINT32(0x0000000F, card->bars[PCI_BAR_IRTE].bar_ptr + HP_EOI_IRQ1);

    rt_spin_unlock_irqrestore(flags, &card->smplock);

    if(irq_handled) {
        rt_enable_irq(card->os_info.irq);
        return IRQ_HANDLED;
    } else {
        static int i = 0;
        if(i < 10) {
            ++i; /* do not pollute syslog */
            DPRLIBERRMSG("Unexpected interrupt IRQ %d. For good realtime don't share it.\n",
                card->os_info.irq);
        }
        rt_pend_linux_irq(card->os_info.irq);

        return IRQ_NONE;
    }
}

static irqreturn_t cp16xx_irq_shared_cbf_rt(int irq, void *dev_id, struct pt_regs *regs)
{
    struct cp16xx_card_data *card = (struct cp16xx_card_data *)dev_id;

    DPR_WAKEUP_QUEUE(card->rt_irq);
    dprlib_int_callback(&card->cp);

    return IRQ_HANDLED;
}

int cp16xx_os_irq_init(struct cp16xx_card_data *card)
{
    int err = -EFAULT;
    DPRLIBLOGMSG("begin\n");

    DPRLIBLOGMSG("request irq %i, card 0x%p\n", card->os_info.irq, card);
    if(card->os_info.irq >= 0) {
        char tmp[200], *ptmp;
        rt_mount_rtai();
        ptmp = RTAI_UNIC_NAME(tmp, RTAI_MAGIC_STARTOP, card->cp_index);
        if(!(card->startop_irq = rt_typed_named_sem_init(ptmp, 0, BIN_SEM))) {
            DPRLIBERRMSG("can't create startop %s semaphore\n", ptmp);
            goto cp16xx_os_init_irq_fail_startop;
        }
        ptmp = RTAI_UNIC_NAME(tmp, RTAI_MAGIC_OPFAULT, card->cp_index);
        if(!(card->opfault_irq = rt_typed_named_sem_init(ptmp, 0, BIN_SEM))) {
            DPRLIBERRMSG("can't create opfault %s semaphore\n", ptmp);
            goto cp16xx_os_init_irq_fail_opfault;
        }
        ptmp = RTAI_UNIC_NAME(tmp, RTAI_MAGIC_NEWCYCLE, card->cp_index);
        if(!(card->newcycle_irq = rt_typed_named_sem_init(ptmp, 0, BIN_SEM))) {
            DPRLIBERRMSG("can't create newcycle %s semaphore\n", ptmp);
            goto cp16xx_os_init_irq_fail_newcycle;
        }

        if((err = rt_request_linux_irq(card->os_info.irq, cp16xx_irq_shared_cbf_rt, "cp16xx",
            card)))
            goto cp16xx_os_init_irq_rt_fail;

        if((err = rt_request_global_irq_ext(card->os_info.irq, (void *)cp16xx_irq_shared_cbf,
            (unsigned long)card)))
            goto cp16xx_os_init_irq_irt_fail;

        rt_enable_irq(card->os_info.irq);

        DPRLIBLOGMSG("request irq %i  -> OK\n", card->os_info.irq);
    }

    cp16xx_irq_set_mode(card);
    cp16xx_irq_restore_mask_rt(card);
    cp16xx_irq_restore_mask_irt(card);

    DPRLIBLOGMSG("end\n");

    return 0;

cp16xx_os_init_irq_irt_fail:
    rt_free_linux_irq(card->os_info.irq, card);
cp16xx_os_init_irq_rt_fail:
    rt_named_sem_delete(card->newcycle_irq);
cp16xx_os_init_irq_fail_newcycle:
    rt_named_sem_delete(card->opfault_irq);
cp16xx_os_init_irq_fail_opfault:
    rt_named_sem_delete(card->startop_irq);
cp16xx_os_init_irq_fail_startop:
    rt_umount_rtai();

    DPRLIBERRMSG("can't get assigned irq %i, error %i\n", card->os_info.irq, err);

    return err;
}

void cp16xx_os_irq_uninit(struct cp16xx_card_data *card)
{
    DPRLIBLOGMSG("begin\n");

    cp16xx_irq_reset_mask_irt(card);
    cp16xx_irq_reset_mask_rt(card);

    if(card->os_info.irq >= 0) {
        rt_free_global_irq(card->os_info.irq);
        rt_free_linux_irq(card->os_info.irq, card);
        rt_named_sem_delete(card->opfault_irq);
        rt_named_sem_delete(card->startop_irq);
        rt_named_sem_delete(card->newcycle_irq);
        rt_umount_rtai();
    }

    DPRLIBLOGMSG("end\n");
}

static ssize_t cp16xx_os_syncronize_irt(struct cp16xx_interface *interface, size_t count)
{
    int ret = -EFAULT;
        DPRLIBERRMSG("compiled with RTAI, don't use read interface for synchronisation\n");

    return ret;
}

#endif /* RTAI */
