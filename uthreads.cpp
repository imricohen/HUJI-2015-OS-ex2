/*
 * uthreads.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: syoels
 */

#include "uthreads.h"
typedef unsigned long address_t;

Thread gThreadlist[MAX_THREAD_NUM];


int uthread_init(int quantum_usecs)
{
	int a,b,c;
    sum:
        c = a+b;
	void* ptr = &&sum;
	address_t main_thread_strt= (address_t)ptr;
	Thread mainThread = new Thread();
	//mainThread->priority = ORANGE;
	gThreadlist[0] = mainThread;

}


/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%fs:0x30,%0\n"
		"rol    $0x11,%0\n"
                 : "=g" (ret)
                 : "0" (addr));
    return ret;
}



