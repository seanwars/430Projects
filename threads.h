//
//  threads.h
//  q
//
//  Created by Shane T. Nelson on 10/12/15.
//  Copyright © 2015 Shane T. Nelson. All rights reserved.
//

#ifndef threads_h
#define threads_h
#include <malloc.h>
#include "q.h"

void start_thread(void (*f)(void))
{
	TCB_t * t = (TCB_t*)malloc(sizeof(TCB_t));	//allocate a TCB_t
	char * s = (char *)_malloca( 8192 );	//allocate a stack
	init_TCB(&t, &f, &s, 8192);
	addQueue(&RunQ, &t);
}

void run()
{
	ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(RunQ->conext));  // start the first thread
}

void yield()
{
	TCB_t *curr, *next;
	curr = RunQ;
	RotateQ(RunQ);
	next = RunQ;
	swapcontext(&(curr->context), &(next->context));
}