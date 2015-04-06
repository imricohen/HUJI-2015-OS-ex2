#include "uthreads.h"
#include <iostream>
#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>


#define SECOND 1000000

void f(void)
{
  printf("enter f\n");
  int i = 100;
  while(--i > 0){
    printf("in f (%d)\n",i);
    usleep(SECOND);
  }
}

void g(void)
{
  printf("enter g\n");
  int i = 100;
  while(--i > 0){
    printf("in g (%d)\n",i);
    usleep(SECOND);
  }
}



int main()
{

	uthread_init(50);

	std::cout << "success\n";
	int a = 5;

	while(a > 0){
		std::cout << "loop "<< a << "\n";
		//usleep(1000000);
		a--;
	}

	//jmp_to_thread(0);

	return 0;
}
