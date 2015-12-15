/*****************************************************************************
*  Copyright (C) SIEMENS CORP., 2015 All rights reserved.
******************************************************************************
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

/*-----------------------------------------------------------------------------
 *  Project     : PROFINET IO
 *  Package     : CP1616 DK
 *  Component   : PROFIenergy ( PE )
 *-----------------------------------------------------------------------------
 *
 *  D e s c r i p t i o n:     Test Main for module tests
 *
 *-----------------------------------------------------------------------------
 *
 *  H i s t o r y:
 *  12.10.2010 PL: first implementation
 *
 *----------------------------------------------------------------------------*/

#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "pniointr.h"

#include "pnio_pe.h"
#include "pnio_pe_util.h"


// global trace variables: are defined in: iobase\src\fct_common.cpp   !!!!!!
// but this file is not used in the test prog  => so we have to define them here
// AND set 'right' values:
//
#if defined(PRN_TRACE_ON) || defined(WDB_TRACE_ON)

unsigned long g_pnio_trc_dest = 1;                           /* trace output destination. 0: no output, 1: stdout printf */
unsigned long g_pnio_trc_group= (GR_INIT | GR_PE);
unsigned long g_pnio_trc_depth= LV_FCTINT;                   /* LV_FCTINT= important internal function calls */;

#endif /* _TRACE_ON */



int tst_1();
int tst_2();
int tst_3();

/*-----------------------------------------------------------------------------
 *  Generate random numbers in the half-closed interval
 *  [range_min, range_max). In other words,
 *  range_min <= random number < range_max
 *
 *  Note: RAND_MAX is a constant defined in <cstdlib>. Its default is 32767.
 *  A typical way to generate pseudo-random numbers in a determined range using rand
 *  is to use the modulo of the returned value by the range span and add the initial
 *  value of the range:
 *  ( value % 100 ) is in the range 0 to 99
 *  ( value % 100 + 1 ) is in the range 1 to 100
 *  ( value % 30 + 1985 ) is in the range 1985 to 2014
 *  Notice though that this modulo operation does not generate a truly uniformly
 *  distributed random number in the span (since in most cases lower numbers are slightly more likely),
 *  but it is generally a good approximation for short spans.
 *  int rnd = rand() % 254 + 1   // is in the range 1 - 255
 *
 *  Note: To seed random generator call: std::srand( (unsigned int)time(NULL) );
 *
 */
unsigned int rangedRand( int range_min, int range_max)
{
   unsigned int u = (unsigned int)((double)rand() / (RAND_MAX + 1) * (range_max - range_min) + range_min);
   return u;
}



/*----------------------------------------------------------------------------*/
/*------------------   main: test entry point --------------------------------*/

int main(int argc, char* argv[])
{
    int ch;
    unsigned int rand_num = 0;

    /* initialize random seed: */
    std::srand( (unsigned int)time(NULL) );

    /* generate random number: */
    rand_num = rangedRand(1,256);


    do
      {
         printf("\nselect a num or 'q' to quit \n");
         ch = _getch();
         ch = tolower( ch );
         if ( ch == 'q' ) {
             printf("test quit\n");
             break;
         }
         switch (ch) {
             case '1':
                 printf("test 1: \n");
                 tst_1();
                 break;
             case '2':
                 printf("test 2: \n");
                 tst_2();
                 break;
             case '3':
                 printf("test 3: \n");
                 tst_3();
                 break;
             default:
                 printf("test unknown: \n");
         } // end switch test_num
      } while(1);

	return 0;
}

/*-----------------------------------------------------------------------------
 * Descr : Queue Ifc Test
 */
int tst_1()
{
    int loop_cnt = 5;


    for (int i=0; i<loop_cnt; i++ ) {
        {
            cPeRqQueue q;
            // cPeReq r1(1), r2(2), r3(3);  ERROR, => delete in q Dtor
            cPeReq *pr = new cPeReq(1);
            q.add_rq(1, pr);
        }
    }

    return 0;
}

/*-----------------------------------------------------------------------------
 * Descr : Main thread & Timer thread: parallel Queue Access Test
 */

/* Dummy Class for controller Instances --- Test simulation only ---
 */
struct IControllerDummy {
    IControllerDummy(void) { m_pPeMgt = NULL;}
    ~IControllerDummy() { delete m_pPeMgt;}

    unsigned int v1;
    unsigned int v2;
    unsigned int v3;
    unsigned int v4;

private:
    cPeMgt  *m_pPeMgt;  // ptr to pe class
};

IControllerDummy controllerDummy;

IController *p_ctrl = (IController*)&controllerDummy;

int tst_2()
{
    int loop_cnt = 16;
    cPeMgt pe_mgt(p_ctrl);

    pe_mgt.init();
    pe_mgt.m_pTimer->start();

    // fill the queue
    for (int i=1; i<32; i++ ) {
        PeRqRefType ref = i;
        int life = rangedRand(1,9);
        cPeReq *pr = new cPeReq(ref, life);
        pe_mgt.add_pe_request(i, pr);
    }

    for (int i=0; i<loop_cnt; i++ ) {
        printf("%04d: test2 main th: \n",loop_cnt);
        Sleep(900);
        PeRqRefType ref = i;
        int life = rangedRand(1,9);
        cPeReq *pr = new cPeReq(ref, life);
        pe_mgt.add_pe_request(i, pr);
    }

    Sleep(15000);
    pe_mgt.uninit();
    return 0;
}

/*-----------------------------------------------------------------------------
 * Descr : tst_3:  STL MAP Container test  (erase element)
 */
int tst_3 ( )
{
    RqList            li;
    RqListIterator    pos;

    int loop_cnt = 5;


    for (int i=0; i<loop_cnt; i++ ) {
        cPeReq *pr = new cPeReq(i);
        li.insert(std::make_pair(i /*ref*/, pr));
    }

#define ERASE_EXAMPLE2
#if defined ERASE_EXAMPLE1
    RqListIterator    pos_2del = li.end();
    for (pos = li.begin(); pos != li.end(); pos++) {
        if (pos_2del != li.end()) {
            li. erase(pos_2del);
        }
        cPeReq *p = pos->second;
        delete p;
        //li. erase(pos);  // <--- ERROR with next pos++ in the loop !!!
        pos_2del = pos;
    } // end for

    if (pos_2del != li.end()) {
        li. erase(pos_2del);
    }
#elif defined ERASE_EXAMPLE2

    pos = li.begin();
    while ( pos != li.end() ) {
        cPeReq *p = pos->second;
        delete p;
        li. erase(pos++);  // <--- OK : Note that pos++ increments pos so that it refers
                           // to the next element but yields a copy of its original value.
    } // end for

#endif
    return 0;
} /* end of tst_3 */

