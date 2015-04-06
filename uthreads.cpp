/*
 * uthreads.cpp
 *
 *  Created on: Apr 5, 2015
 *      Author: syoels
 */

#include "uthreads.h"
#include <stdlib.h>
#include "Thread.h"
#include <iostream>
#include <map>
#include <cmath>
#include <queue>
#include <signal.h>
#include <sys/time.h>

typedef unsigned long address_t;
typedef struct itimerval itimerval;

std::map<int, Thread*> gThreadlist;
Thread* gRunning;
std::queue<Thread*> gReady;
int gQuantom;
itimerval gTimer;



int uthread_init(int quantum_usecs)
{

	//prepare main thread 0
	void* memaddr = __builtin_return_address(0);
	Thread *mainThread = new Thread(0, memaddr, ORANGE);
	gThreadlist[0] = mainThread;
	gRunning = gThreadlist[0];
	gRunning->setQueue(RUNNING);

	//define quantum measures and set timer
	gQuantom = quantum_usecs;
	timerInit();

	//keep working from here as long jump
	jmp_to_thread(0);

	while(true){
		//check if queue is empty (only thread 0): terminate(0) and exit
		//otherwise: skip quantom
	}

	return 0;

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

void timerInit()
{
	int secs = floor(gQuantom/(10^6));
	int micsecs = gQuantom - secs*(10^6);

	signal(SIGVTALRM, timer_handler);
	gTimer.it_value.tv_sec = secs;  /* first time interval, seconds part */
	gTimer.it_value.tv_usec = micsecs; /* first time interval, microseconds part */
	gTimer.it_interval.tv_sec = secs;  /* following time intervals, seconds part */
	gTimer.it_interval.tv_usec = micsecs; /* following time intervals, microseconds part */

	setitimer(ITIMER_VIRTUAL, &gTimer, NULL);
}

void timer_handler(int signal)
{
	swithThreads(READY);
}

/**
 * move running thread to q Queue, and pop a new running thread.
 */
void swithThreads(Queue q)
{

	//stop timer
	__sigset_t sigSet;
	sigemptyset(&sigSet);
	sigaddset(&sigSet, SIGVTALRM);
	sigprocmask(SIG_BLOCK, &sigSet, NULL);

	std::cout << "In Switch\n";

	bool isReadyEmpty = gReady.empty();
	if(isReadyEmpty)
	{

	}

	else
	{
		Thread* newRunning = gReady.front();
		newRunning->setQueue(RUNNING);
		gRunning->setQueue(READY);

		bool justReturned = sigsetjmp(*gRunning->getThreadSnapshot(), 1);
		if(justReturned){
		}

		else{
			gReady.push(gRunning);
			gRunning = newRunning;
		}


	//return timer
	sigprocmask(SIG_UNBLOCK, &sigSet, NULL);
	setitimer(ITIMER_VIRTUAL, &gTimer, NULL);

	}

}


void jmp_to_thread(int id){

	siglongjmp(*gThreadlist[id]->getThreadSnapshot(),1);
}



//some comments for git test
