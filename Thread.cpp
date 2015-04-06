#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include "Thread.h"



Thread::Thread(int id ,void* location, Priority priority)
: _id(id), _priority(priority), _currQueue(READY)
{
    _stack = new char[STACK_SIZE];

    address_t sp, pc;
    sp = (address_t)_stack + STACK_SIZE - sizeof(address_t);
    pc = (address_t)location;
    sigsetjmp(_threadSnapshot, 1);
    (_threadSnapshot->__jmpbuf)[JB_SP] = translate_address(sp);
    (_threadSnapshot->__jmpbuf)[JB_PC] = translate_address(pc);
    sigemptyset(&_threadSnapshot->__saved_mask);

}

//df
Thread::~Thread()
{
    delete _stack;
}

int Thread::getID() const
{
	return _id;
}

char* Thread::getStack() const
{
    return _stack;
}

sigjmp_buf* Thread::getThreadSnapshot()
{
	return &_threadSnapshot;
}


Priority Thread::getPriority() const
{
	return _priority;
}

void Thread::setQueue(Queue queue)
{
	_currQueue = queue;
}

void this_does_nothing(void){

}

Queue Thread::getQueue() const
{
	return _currQueue;
}

