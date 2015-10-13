//
//  thread_test.c
//  q
//
//  Created by Sean C Bennett on 10/12/15.
//  Created by Shane T. Nelson on 10/12/15.
//  Copyright © 2015 Shane T. Nelson. All rights reserved.
//

#define _XOPEN_SOURCE 600
#include "threads.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

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
	runQ = InitQueue();
	start_thread(f1);
	start_thread(f2);
	run();
}
