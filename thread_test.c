//
//  thread_test.c
//  q
//
//  Created by Shane T. Nelson on 10/12/15.
//  Copyright © 2015 Shane T. Nelson. All rights reserved.
//

#include "threads.h"

Queue * RunQ; //global header pointer to TCB

int global = 0; //global variable for testing
//function for thread testing
void f1()
{
	int local = 0;
	while(1)
	{
		printf("Thread from F1: %d, %d", local++, global++);
		sleep(1);	//slow down thread
		yield();	//wait to be preempted
	}
}
//function for thread testing
void f2()
{
	int local = 0;
	while(1)
	{
		printf("Thread from F2: %d, %d", local++, global++);
		sleep(1);	//slow down thread
		yield();	//wait to be preempted
	}
}

void main()
{
	RunQ = InitQueue();
	start_thread(f1);
	start_thread(f2);
	run();
}
