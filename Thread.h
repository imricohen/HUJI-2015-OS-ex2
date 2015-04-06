/*
 * thread.h
 *
 *  Created on: Mar 19, 2015
 *      Author: moshemandel
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <setjmp.h>
#include "uthreads.h"

//hi man
#ifdef __x86_64__
/* code for 64 bit Intel arch */
	typedef unsigned long address_t;
	#define JB_SP 6
	#define JB_PC 7

#else
/* code for 32 bit Intel arch */
	typedef unsigned int address_t;
	#define JB_SP 4
	#define JB_PC 5
#endif

address_t translate_address(address_t addr);

class Thread
{
public:

	Thread(int id, Priority priority);

	Thread(int id ,void (*location)(void), Priority priority);

	~Thread();

	int getID() const;

	char* getStack() const;

	sigjmp_buf* getThreadSnapshot() ;


	Priority getPriority() const;

	void setQueue(Queue queue);

	Queue getQueue() const;


private:
	int _id;
	char *_stack;
	sigjmp_buf _threadSnapshot;
	Priority _priority;
	Queue _currQueue;
};


#endif /* THREAD_H_ */

